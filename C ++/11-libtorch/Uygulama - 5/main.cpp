// ---------------------------------------------------------
// LibTorch + OpenCV ile TorchScript model inference örneği
// ---------------------------------------------------------
// Bu dosyada:
//  - TorchScript modeli (model_ts.pt) yüklüyorum
//  - OpenCV ile bir görüntü (test.jpg) okuyorum
//  - cv::Mat -> torch::Tensor (BGR -> RGB, resize, normalize) yapıyorum
//  - module.forward() ile tahmin alıyorum
//  - softmax + argmax ile sınıf index'ini hesaplıyorum
// ---------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>

#include <torch/script.h>     // TorchScript API
#include <opencv2/opencv.hpp> // OpenCV ana header

// ---------------------------------------------------------
// cv::Mat (BGR) -> torch::Tensor [1, 3, H, W]
// ---------------------------------------------------------
// Adımlar:
//  1) Resize (H x W)
//  2) BGR -> RGB
//  3) uint8 -> float32, 0-1 normalize
//  4) HWC -> NHWC -> NCHW (PyTorch formatı)
//  5) clone() ile bellek güvence altına alma
torch::Tensor preprocess_image(const cv::Mat &img_bgr, int target_size)
{
    cv::Mat img;

    // Orijinal görüntüyü kopyala (orijinale dokunmamak için)
    img_bgr.copyTo(img);

    // 1) Resize (W x H)
    cv::resize(img, img, cv::Size(target_size, target_size));

    // 2) BGR -> RGB (OpenCV BGR kullanır, model genelde RGB bekler)
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);

    // 3) uint8 -> float32 + normalize 0-1
    cv::Mat img_float;
    img.convertTo(img_float, CV_32F, 1.0f / 255.0f);

    // 4) HWC -> NHWC formatında tensöre çevir
    auto tensor_image = torch::from_blob(
        img_float.data,
        {1, img_float.rows, img_float.cols, 3}, // [N, H, W, C]
        torch::TensorOptions().dtype(torch::kFloat32));

    // 5) NHWC -> NCHW (PyTorch standardı)
    tensor_image = tensor_image.permute({0, 3, 1, 2}); // [N, C, H, W]

    // contiguous + clone: OpenCV belleğinden ayrıştırmak için
    tensor_image = tensor_image.contiguous().clone();

    return tensor_image;
}

// ---------------------------------------------------------
// TorchScript module üzerinde inference fonksiyonu
// ---------------------------------------------------------
torch::Tensor run_inference(torch::jit::script::Module &module,
                            const torch::Tensor &input)
{
    // TorchScript forward() IValue listesi bekler
    std::vector<torch::jit::IValue> inputs;
    inputs.push_back(input);

    // module.forward() -> IValue, toTensor() ile tensöre çevir
    torch::Tensor output = module.forward(inputs).toTensor();
    return output;
}

int main()
{
    try
    {
        std::cout << "[INFO] Program basladi.\n";

        // ------------------------------
        // 1) Model dosya yolu
        // ------------------------------
        const std::string model_path = "model_ts.pt";

        // Dosya gerçekten var mı kontrol et
        {
            std::ifstream f(model_path);
            if (!f.good())
            {
                std::cerr << "[HATA] model_ts.pt bulunamadi!\n";
                std::cerr << "       model_ts.pt dosyasini exe ile ayni klasore koy.\n";
                std::cout << "Enter'a basip cikabilirsin...\n";
                std::cin.get();
                return -1;
            }
        }

        // ------------------------------
        // 2) TorchScript modeli yükle
        // ------------------------------
        std::cout << "[INFO] Model yukleniyor...\n";
        torch::jit::script::Module module = torch::jit::load(model_path);

        // CPU kullanıyoruz (GPU varsa kCUDA da kullanılabilir)
        module.to(torch::kCPU);
        module.eval();
        std::cout << "[OK] Model yuklendi ve eval modunda.\n";

        // ------------------------------
        // 3) Test resmi oku
        // ------------------------------
        const std::string image_path = "test.jpg"; // exe ile aynı klasörde olmalı
        cv::Mat img_bgr = cv::imread(image_path);

        if (img_bgr.empty())
        {
            std::cerr << "[HATA] Resim yuklenemedi: " << image_path << "\n";
            std::cerr << "       test.jpg dosyasini exe ile ayni klasore koy.\n";
            std::cout << "Enter'a basip cikabilirsin...\n";
            std::cin.get();
            return -1;
        }

        std::cout << "[OK] Resim yuklendi. Boyut: "
                  << img_bgr.cols << "x" << img_bgr.rows << " (W x H)\n";

        // ------------------------------
        // 4) Preprocess -> Tensor
        // ------------------------------
        int target_size = 64; // Python tarafında Resize((64,64)) kullandık
        torch::Tensor input_tensor = preprocess_image(img_bgr, target_size);

        std::cout << "[DEBUG] Input tensor shape: " << input_tensor.sizes() << "\n";

        // Beklenen shape: [1, 3, 64, 64]
        auto sizes = input_tensor.sizes();
        if (!(sizes.size() == 4 &&
              sizes[0] == 1 &&
              sizes[1] == 3 &&
              sizes[2] == target_size &&
              sizes[3] == target_size))
        {
            std::cerr << "[HATA] Input tensor beklenenden farkli! Gelen: "
                      << sizes << "\n";
            std::cout << "Enter'a basip cikabilirsin...\n";
            std::cin.get();
            return -1;
        }

        // ------------------------------
        // 5) Inference (forward)
        // ------------------------------
        std::cout << "[INFO] Inference calistiriliyor...\n";
        torch::Tensor output = run_inference(module, input_tensor);

        std::cout << "[DEBUG] Output tensor shape: " << output.sizes() << "\n";

        // ------------------------------
        // 6) Postprocess: softmax + argmax
        // ------------------------------
        // Çıkış tensörü: [1, num_classes] (örn. [1, 10])
        torch::Tensor probs = torch::softmax(output, 1); // sınıf olasılıkları
        torch::Tensor pred_class = probs.argmax(1);      // en yüksek olasılıklı sınıf index'i

        std::cout << "Output (logits): " << output << "\n";
        std::cout << "Predicted class index: "
                  << pred_class.item<int>() << "\n";

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
