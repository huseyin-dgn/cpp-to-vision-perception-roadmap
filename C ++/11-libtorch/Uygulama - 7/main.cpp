// ---------------------------------------------------------
// LibTorch + OpenCV ile Gerçek Zamanlı Webcam Inference
// (ImprovedCNN + CIFAR10 Normalize)
// ---------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <torch/script.h>
#include <opencv2/opencv.hpp>

// CIFAR-10 sınıf isimleri
const std::vector<std::string> CIFAR10_CLASSES = {
    "airplane",   // 0
    "automobile", // 1
    "bird",       // 2
    "cat",        // 3
    "deer",       // 4
    "dog",        // 5
    "frog",       // 6
    "horse",      // 7
    "ship",       // 8
    "truck"       // 9
};

// CIFAR-10 Normalize değerleri (PyTorch ile aynı)
const float CIFAR10_MEAN[3] = {0.4914f, 0.4822f, 0.4465f}; // R, G, B
const float CIFAR10_STD[3] = {0.2470f, 0.2435f, 0.2616f};

torch::Tensor preprocess_image(const cv::Mat &img_bgr, int target_size)
{
    cv::Mat img;
    img_bgr.copyTo(img);

    // Resize
    cv::resize(img, img, cv::Size(target_size, target_size));

    // BGR -> RGB
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);

    // uint8 -> float32 [0,1]
    cv::Mat img_float;
    img.convertTo(img_float, CV_32F, 1.0f / 255.0f);

    // Kanal bazlı normalize
    {
        std::vector<cv::Mat> channels(3);
        cv::split(img_float, channels); // R,G,B

        for (int c = 0; c < 3; ++c)
        {
            channels[c] = (channels[c] - CIFAR10_MEAN[c]) / CIFAR10_STD[c];
        }

        cv::merge(channels, img_float);
    }

    // HWC -> NHWC tensor
    auto tensor_image = torch::from_blob(
        img_float.data,
        {1, img_float.rows, img_float.cols, 3}, // [N,H,W,C]
        torch::TensorOptions().dtype(torch::kFloat32));

    // NHWC -> NCHW
    tensor_image = tensor_image.permute({0, 3, 1, 2}); // [N,C,H,W]

    // Belleği sabitle
    tensor_image = tensor_image.contiguous().clone();

    return tensor_image;
}

torch::Tensor run_inference(torch::jit::script::Module &module,
                            const torch::Tensor &input)
{
    std::vector<torch::jit::IValue> inputs;
    inputs.push_back(input);
    torch::Tensor output = module.forward(inputs).toTensor();
    return output;
}

int main()
{
    try
    {
        std::cout << "[INFO] Program basladi.\n";

        // ------------------------------
        // 1) Modeli yükle
        // ------------------------------
        const std::string model_path = "model_ts.pt";

        {
            std::ifstream f(model_path);
            if (!f.good())
            {
                std::cerr << "[HATA] model_ts.pt bulunamadi! Beklenen yer: "
                          << model_path << "\n";
                std::cout << "Enter'a basip cikabilirsin...\n";
                std::cin.get();
                return -1;
            }
        }

        std::cout << "[INFO] Model yukleniyor...\n";
        torch::jit::script::Module module = torch::jit::load(model_path);
        module.to(torch::kCPU);
        module.eval();
        std::cout << "[OK] Model yüklendi, CPU'da ve eval modunda.\n";

        // ------------------------------
        // 2) Webcam aç
        // ------------------------------
        cv::VideoCapture cap(0); // 0 = varsayilan kamera

        if (!cap.isOpened())
        {
            std::cerr << "[HATA] Kamera acilamadi!\n";
            std::cout << "Enter'a basip cikabilirsin...\n";
            std::cin.get();
            return -1;
        }

        std::cout << "[INFO] Webcam acildi. 'q' tusuna basarak cikabilirsin.\n";

        const int target_size = 64;

        while (true)
        {
            cv::Mat frame;
            cap >> frame; // kameradan bir frame oku

            if (frame.empty())
            {
                std::cerr << "[WARN] Bos frame geldi, devam ediyorum...\n";
                continue;
            }

            // ------------------------------
            // 3) Preprocess -> Tensor
            // ------------------------------
            torch::Tensor input_tensor = preprocess_image(frame, target_size);

            // ------------------------------
            // 4) Inference
            // ------------------------------
            torch::Tensor output = run_inference(module, input_tensor);

            // ------------------------------
            // 5) Postprocess: softmax + argmax
            // ------------------------------
            torch::Tensor probs = torch::softmax(output, 1);
            torch::Tensor pred_class = probs.argmax(1);

            int pred_idx = pred_class.item<int>();
            std::string pred_name = "unknown";

            if (pred_idx >= 0 && pred_idx < static_cast<int>(CIFAR10_CLASSES.size()))
            {
                pred_name = CIFAR10_CLASSES[pred_idx];
            }

            // ------------------------------
            // 6) Sonucu frame üzerine yaz
            // ------------------------------
            std::string text = "Pred: " + pred_name + " (idx=" + std::to_string(pred_idx) + ")";
            cv::putText(frame, text,
                        cv::Point(10, 30),
                        cv::FONT_HERSHEY_SIMPLEX,
                        0.8,
                        cv::Scalar(0, 255, 0),
                        2);

            // FPS vs. istersek buraya ekleyebiliriz.

            // Frame'i göster
            cv::imshow("Real-time CIFAR10 Inference", frame);

            // 'q' veya ESC ile cik
            char key = static_cast<char>(cv::waitKey(1));
            if (key == 'q' || key == 27)
            {
                std::cout << "[INFO] Kullanici cikis istegi verdi.\n";
                break;
            }
        }

        cap.release();
        cv::destroyAllWindows();

        std::cout << "[INFO] Program sonlandi. Enter'a basip cikabilirsin...\n";
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
