#include <iostream>
#include <fstream>
#include <torch/script.h>
#include <opencv2/opencv.hpp>

int main()
{
    try
    {
        std::cout << "[INFO] Program basladi.\n";

        // 0) MODEL DOSYASI VAR MI? ÖNCE ONU KONTROL ET
        const std::string model_path = "model_ts.pt";
        {
            std::ifstream f(model_path);
            if (!f.good())
            {
                std::cerr << "[HATA] model_ts.pt BULUNAMADI!" << std::endl;
                std::cerr << "       Su an calisan exe hangi klasorde?\n";
                std::cerr << "       model_ts.pt dosyasini EXE ile AYNI klasore koymalisin.\n";
                std::cout << "Devam etmek icin Enter'a bas...\n";
                std::cin.get();
                return -1;
            }
            else
            {
                std::cout << "[OK] model_ts.pt bulundu. Yuklemeye geciyorum...\n";
            }
        }

        // 1) TorchScript CNN modelini yükle
        torch::jit::script::Module module = torch::jit::load(model_path);
        std::cout << "[OK] Model yüklendi: " << model_path << std::endl;

        torch::Device device(torch::kCPU);
        module.to(device);
        module.eval();
        std::cout << "[OK] Model CPU'ya tasindi ve eval moduna alindi.\n";

        // 2) Resmi oku
        const std::string image_path = "test.jpg";
        cv::Mat img = cv::imread(image_path);
        if (img.empty())
        {
            std::cerr << "[HATA] Resim yuklenemedi: " << image_path << std::endl;
            std::cerr << "       test.jpg dosyasini da EXE ile AYNI klasore koy.\n";
            std::cout << "Devam etmek icin Enter'a bas...\n";
            std::cin.get();
            return -1;
        }

        std::cout << "[OK] Orijinal resim boyutu: "
                  << img.cols << "x" << img.rows << " (W x H)" << std::endl;

        // 3) 64x64'e resize
        cv::resize(img, img, cv::Size(64, 64));
        std::cout << "[OK] Resim 64x64'e yeniden boyutlandirildi.\n";

        // 4) BGR -> RGB
        cv::cvtColor(img, img, cv::COLOR_BGR2RGB);

        // 5) uint8 -> float32 ve 0–1
        cv::Mat img_float;
        img.convertTo(img_float, CV_32F, 1.0 / 255.0);
        std::cout << "[OK] Resim float ve normalize hale getirildi.\n";

        // 6) HWC -> tensor (N, H, W, C)
        auto tensor_image = torch::from_blob(
            img_float.data,
            {1, img_float.rows, img_float.cols, 3}, // [1, 64, 64, 3]
            torch::TensorOptions().dtype(torch::kFloat32).device(device));

        // 7) NHWC -> NCHW
        tensor_image = tensor_image.permute({0, 3, 1, 2}).contiguous();
        tensor_image = tensor_image.clone(); // OpenCV belleğinden bagimsiz kopya

        std::cout << "[OK] Input tensor shape (NCHW): " << tensor_image.sizes() << std::endl;

        // 8) Forward için input listesi
        std::vector<torch::jit::IValue> inputs;
        inputs.push_back(tensor_image);

        std::cout << "[INFO] Forward baslatiliyor...\n";
        torch::Tensor output = module.forward(inputs).toTensor();
        std::cout << "[OK] Forward bitti.\n";
        std::cout << "Output shape: " << output.sizes() << std::endl;

        // 9) Softmax + argmax
        torch::Tensor probs = torch::softmax(output, 1);
        torch::Tensor pred_class = probs.argmax(1);

        std::cout << "Output (logits): " << output << std::endl;
        std::cout << "Output (probs): " << probs << std::endl;
        std::cout << "Predicted class index: " << pred_class.item<int>() << std::endl;

        std::cout << "Program bitti. Cikmak icin Enter'a bas...\n";
        std::cin.get();
    }
    catch (const c10::Error &e)
    {
        std::cerr << "[EXCEPTION - c10] " << e.what() << std::endl;
        std::cout << "Cikmak icin Enter'a bas...\n";
        std::cin.get();
        return -1;
    }
    catch (const std::exception &e)
    {
        std::cerr << "[EXCEPTION - std] " << e.what() << std::endl;
        std::cout << "Cikmak icin Enter'a bas...\n";
        std::cin.get();
        return -1;
    }

    return 0;
}
