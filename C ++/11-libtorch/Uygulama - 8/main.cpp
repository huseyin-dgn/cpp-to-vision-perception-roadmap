// ---------------------------------------------------------
// YOLOv8 TorchScript + LibTorch + OpenCV
//  - Tek görselde nesne tespiti (en iyi tek kutu)
//  - Webcam ile gerçek zamanlı nesne tespiti (en iyi tek kutu)
//  - NMS yok, sadece en yüksek skorlu box seçiliyor
// ---------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include <torch/script.h>
#include <opencv2/opencv.hpp>

// COCO sınıf isimleri (80 sınıf)
const std::vector<std::string> COCO_CLASSES = {
    "person", "bicycle", "car", "motorcycle", "airplane", "bus", "train", "truck", "boat",
    "traffic light", "fire hydrant", "stop sign", "parking meter", "bench", "bird", "cat",
    "dog", "horse", "sheep", "cow", "elephant", "bear", "zebra", "giraffe", "backpack",
    "umbrella", "handbag", "tie", "suitcase", "frisbee", "skis", "snowboard", "sports ball",
    "kite", "baseball bat", "baseball glove", "skateboard", "surfboard", "tennis racket",
    "bottle", "wine glass", "cup", "fork", "knife", "spoon", "bowl", "banana", "apple",
    "sandwich", "orange", "broccoli", "carrot", "hot dog", "pizza", "donut", "cake", "chair",
    "couch", "potted plant", "bed", "dining table", "toilet", "tv", "laptop", "mouse", "remote",
    "keyboard", "cell phone", "microwave", "oven", "toaster", "sink", "refrigerator",
    "book", "clock", "vase", "scissors", "teddy bear", "hair drier", "toothbrush"};

// ---------------------------------------------------------
// Preprocess: cv::Mat (BGR) -> torch::Tensor [1, 3, input_size, input_size]
// ---------------------------------------------------------
torch::Tensor preprocess_image(const cv::Mat &img_bgr, int input_size = 640)
{
    cv::Mat img;

    // BGR -> RGB
    cv::cvtColor(img_bgr, img, cv::COLOR_BGR2RGB);

    // Resize (YOLOv8 genelde kare giriş: 640x640)
    cv::resize(img, img, cv::Size(input_size, input_size));

    // uint8 -> float32, 0-1
    img.convertTo(img, CV_32F, 1.0f / 255.0f);

    // HWC -> NHWC tensöre çevir
    auto tensor_image = torch::from_blob(
        img.data,
        {1, input_size, input_size, 3}, // [N,H,W,C]
        torch::TensorOptions().dtype(torch::kFloat32));

    // NHWC -> NCHW
    tensor_image = tensor_image.permute({0, 3, 1, 2}); // [1,3,640,640]

    // contiguous + clone: OpenCV belleğinden ayrıştır
    tensor_image = tensor_image.contiguous().clone();

    return tensor_image;
}

// ---------------------------------------------------------
// YOLOv8 forward çıktılarını tensöre çevirme
// (TorchScript output: Tensor / Tuple / List olabilir)
// ---------------------------------------------------------
torch::Tensor get_detections_tensor(const torch::jit::IValue &output)
{
    if (output.isTensor())
    {
        return output.toTensor();
    }
    else if (output.isTuple())
    {
        auto elements = output.toTuple()->elements();
        if (!elements.empty() && elements[0].isTensor())
        {
            return elements[0].toTensor();
        }
    }
    else if (output.isList())
    {
        auto list = output.toList();
        if (list.size() > 0 && list.get(0).isTensor())
        {
            return list.get(0).toTensor();
        }
    }

    throw std::runtime_error("Beklenmeyen YOLOv8 output formati (Tensor/Tuple/List degil).");
}

// ---------------------------------------------------------
// En iyi tek box için struct
// ---------------------------------------------------------
struct BestDet
{
    float x1, y1, x2, y2;
    float score;
    int cls_id;
    bool valid;
};

// ---------------------------------------------------------
// YOLOv8 ham çıktısından (nms=False) en iyi kutuyu seç
// Beklenen format (satır bazında kabaca):
//   [x, y, w, h, obj_conf, cls0_conf, cls1_conf, ...]
// ---------------------------------------------------------
BestDet get_best_box_from_yolo(const torch::Tensor &det,
                               int img_w, int img_h,
                               float conf_threshold)
{
    BestDet best;
    best.valid = false;
    best.score = 0.0f;
    best.cls_id = -1;

    if (det.dim() != 2 || det.size(0) == 0)
        return best;

    const int num_boxes = det.size(0);
    const int num_attrs = det.size(1);

    if (num_attrs < 6)
    {
        std::cerr << "[WARN] YOLO output attr sayisi cok dusuk: " << num_attrs << "\n";
        return best;
    }

    for (int i = 0; i < num_boxes; ++i)
    {
        auto row = det[i];

        float cx = row[0].item<float>();
        float cy = row[1].item<float>();
        float w = row[2].item<float>();
        float h = row[3].item<float>();

        float obj_conf = row[4].item<float>();

        // Sınıf skorları 5. indexten itibaren
        int best_cls = -1;
        float best_cls_score = 0.0f;

        for (int j = 5; j < num_attrs; ++j)
        {
            float cls_score = row[j].item<float>();
            if (cls_score > best_cls_score)
            {
                best_cls_score = cls_score;
                best_cls = j - 5; // 0–79 arası COCO sınıf indexi
            }
        }

        // Toplam skor = obj_conf * class_conf
        float total_score = obj_conf * best_cls_score;

        if (total_score < conf_threshold)
            continue;

        if (!best.valid || total_score > best.score)
        {
            // cx,cy,w,h -> x1,y1,x2,y2
            float x1 = cx - w / 2.0f;
            float y1 = cy - h / 2.0f;
            float x2 = cx + w / 2.0f;
            float y2 = cy + h / 2.0f;

            // Görüntü sınırlarına kırp
            x1 = std::max(0.0f, std::min(x1, static_cast<float>(img_w - 1)));
            y1 = std::max(0.0f, std::min(y1, static_cast<float>(img_h - 1)));
            x2 = std::max(0.0f, std::min(x2, static_cast<float>(img_w - 1)));
            y2 = std::max(0.0f, std::min(y2, static_cast<float>(img_h - 1)));

            best.x1 = x1;
            best.y1 = y1;
            best.x2 = x2;
            best.y2 = y2;
            best.score = total_score;
            best.cls_id = best_cls;
            best.valid = true;
        }
    }

    return best;
}

// ---------------------------------------------------------
// Tek görsel üzerinde YOLOv8 inference (en iyi tek box)
// ---------------------------------------------------------
void run_on_image(torch::jit::script::Module &module,
                  const std::string &image_path,
                  const std::string &save_path = "output.jpg",
                  float conf_threshold = 0.25f)
{
    cv::Mat img_bgr = cv::imread(image_path);
    if (img_bgr.empty())
    {
        std::cerr << "[HATA] Resim yuklenemedi: " << image_path << "\n";
        return;
    }

    std::cout << "[INFO] Resim yuklendi: " << image_path
              << "  Boyut: " << img_bgr.cols << "x" << img_bgr.rows << "\n";

    // Gösterim için 640x640'lik kopya
    cv::Mat vis;
    cv::resize(img_bgr, vis, cv::Size(640, 640));

    torch::NoGradGuard no_grad;

    // Preprocess
    torch::Tensor input_tensor = preprocess_image(img_bgr, 640);

    // Forward
    std::vector<torch::jit::IValue> inputs;
    inputs.push_back(input_tensor);

    torch::jit::IValue output_iv = module.forward(inputs);

    // Çıktıyı tensöre çevir
    torch::Tensor det = get_detections_tensor(output_iv);

    // Beklenen çıkış çoğunlukla [1, num_boxes, num_attrs]
    if (det.dim() == 3 && det.size(0) == 1)
    {
        det = det.squeeze(0); // [num_boxes, num_attrs]
    }

    if (det.dim() != 2)
    {
        std::cerr << "[WARN] Beklenmeyen detection tensor shape: " << det.sizes() << "\n";
        return;
    }

    int img_w = 640;
    int img_h = 640;

    BestDet best = get_best_box_from_yolo(det, img_w, img_h, conf_threshold);

    if (!best.valid)
    {
        std::cout << "[INFO] Threshold'u gecen kutu bulunamadi.\n";
    }
    else
    {
        cv::Rect rect(
            cv::Point(static_cast<int>(best.x1), static_cast<int>(best.y1)),
            cv::Point(static_cast<int>(best.x2), static_cast<int>(best.y2)));

        std::string label = "id=" + std::to_string(best.cls_id);
        if (best.cls_id >= 0 && best.cls_id < static_cast<int>(COCO_CLASSES.size()))
        {
            label = COCO_CLASSES[best.cls_id] + " " + cv::format("%.2f", best.score);
        }

        cv::rectangle(vis, rect, cv::Scalar(0, 255, 0), 2);

        int baseLine = 0;
        cv::Size label_size = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
        cv::Rect bg_rect(
            cv::Point(rect.x, rect.y - label_size.height - baseLine),
            cv::Size(label_size.width, label_size.height + baseLine));

        cv::rectangle(vis, bg_rect, cv::Scalar(0, 255, 0), cv::FILLED);
        cv::putText(vis, label,
                    cv::Point(rect.x, rect.y - baseLine),
                    cv::FONT_HERSHEY_SIMPLEX,
                    0.5, cv::Scalar(0, 0, 0), 1);
    }

    cv::imshow("YOLOv8 - Image (Best Box Only)", vis);
    cv::imwrite(save_path, vis);
    std::cout << "[INFO] Sonuc kaydedildi: " << save_path << "\n";
    std::cout << "[INFO] Pencereyi kapatmak icin bir tusa bas.\n";
    cv::waitKey(0);
}

void run_on_webcam(torch::jit::script::Module &module,
                   int cam_index = 0,
                   float conf_threshold = 0.25f)
{
    cv::VideoCapture cap(cam_index);
    if (!cap.isOpened())
    {
        std::cerr << "[HATA] Kamera acilamadi! Index: " << cam_index << "\n";
        return;
    }

    std::cout << "[INFO] Webcam acildi. Cikis icin 'q' veya ESC.\n";

    torch::NoGradGuard no_grad;

    while (true)
    {
        cv::Mat frame_bgr;
        cap >> frame_bgr;
        if (frame_bgr.empty())
        {
            std::cerr << "[WARN] Bos frame alindi, devam ediyorum...\n";
            continue;
        }

        // Gösterim için 640x640'lik bir kopya
        cv::Mat vis;
        cv::resize(frame_bgr, vis, cv::Size(640, 640));
        int img_w = 640;
        int img_h = 640;

        torch::Tensor input_tensor = preprocess_image(frame_bgr, 640);

        std::vector<torch::jit::IValue> inputs;
        inputs.push_back(input_tensor);

        torch::jit::IValue output_iv = module.forward(inputs);
        torch::Tensor det = get_detections_tensor(output_iv);

        if (det.dim() == 3 && det.size(0) == 1)
            det = det.squeeze(0); // [num_boxes, num_attrs]

        if (det.dim() == 2)
        {
            BestDet best = get_best_box_from_yolo(det, img_w, img_h, conf_threshold);

            if (best.valid)
            {
                cv::Rect rect(
                    cv::Point(static_cast<int>(best.x1), static_cast<int>(best.y1)),
                    cv::Point(static_cast<int>(best.x2), static_cast<int>(best.y2)));

                std::string label = "id=" + std::to_string(best.cls_id);
                if (best.cls_id >= 0 && best.cls_id < static_cast<int>(COCO_CLASSES.size()))
                {
                    label = COCO_CLASSES[best.cls_id] + " " + cv::format("%.2f", best.score);
                }

                cv::rectangle(vis, rect, cv::Scalar(0, 255, 0), 2);
                int baseLine = 0;
                cv::Size label_size = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
                cv::Rect bg_rect(
                    cv::Point(rect.x, rect.y - label_size.height - baseLine),
                    cv::Size(label_size.width, label_size.height + baseLine));

                cv::rectangle(vis, bg_rect, cv::Scalar(0, 255, 0), cv::FILLED);
                cv::putText(vis, label,
                            cv::Point(rect.x, rect.y - baseLine),
                            cv::FONT_HERSHEY_SIMPLEX,
                            0.5, cv::Scalar(0, 0, 0), 1);
            }
        }

        cv::imshow("YOLOv8 - Webcam (Best Box Only)", vis);
        char key = static_cast<char>(cv::waitKey(1));
        if (key == 'q' || key == 27)
        {
            std::cout << "[INFO] Kullanici cikis istedi.\n";
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
}

// ---------------------------------------------------------
// main: tek exe, iki mod
//   - image  -> tek görsel
//   - webcam -> canlı akış
// ---------------------------------------------------------
int main(int argc, char **argv)
{
    try
    {
        std::cout << "[INFO] YOLOv8 C++ uygulamasi basladi.\n";

        // TorchScript model dosyasi adi
        const std::string model_path = "yolov8_ts.pt"; // Python'da ne isimle kaydettiysen onu yaz

        // Model dosyasi kontrol
        {
            std::ifstream f(model_path);
            if (!f.good())
            {
                std::cerr << "[HATA] Model dosyasi bulunamadi: " << model_path << "\n";
                std::cout << "Enter'a basip cikabilirsin...\n";
                std::cin.get();
                return -1;
            }
        }

        std::cout << "[INFO] Model yukleniyor: " << model_path << "\n";
        torch::jit::script::Module module = torch::jit::load(model_path);
        module.to(torch::kCPU);
        module.eval();
        std::cout << "[OK] Model yuklendi ve eval modunda.\n";

        std::string mode = "image";
        if (argc >= 2)
        {
            mode = std::string(argv[1]);
        }

        if (mode == "image")
        {
            std::string image_path = "test.jpg";
            if (argc >= 3)
            {
                image_path = std::string(argv[2]);
            }
            std::cout << "[INFO] Mod: IMAGE  |  Dosya: " << image_path << "\n";
            run_on_image(module, image_path, "output.jpg", 0.25f);
        }
        else if (mode == "webcam")
        {
            std::cout << "[INFO] Mod: WEBCAM\n";
            run_on_webcam(module, 0, 0.25f);
        }
        else
        {
            std::cerr << "[WARN] Bilinmeyen mod: " << mode << "\n";
            std::cerr << "Kullanim:\n";
            std::cerr << "  " << argv[0] << " image [resim_yolu]\n";
            std::cerr << "  " << argv[0] << " webcam\n";
        }

        std::cout << "[INFO] Program bitti. Enter'a basip cikabilirsin...\n";
        std::cin.get();
    }
    catch (const c10::Error &e)
    {
        std::cerr << "[EXCEPTION - c10] " << e.what() << "\n";
        std::cout << "Enter'a basip cikabilirsin...\n";
        std::cin.get();
        return -1;
    }
    catch (const std::exception &e)
    {
        std::cerr << "[EXCEPTION - std] " << e.what() << "\n";
        std::cout << "Enter'a basip cikabilirsin...\n";
        std::cin.get();
        return -1;
    }

    return 0;
}
