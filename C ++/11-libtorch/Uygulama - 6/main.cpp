// ---------------------------------------------------------
// LibTorch + OpenCV ile TorchScript model inference örneği
// (ImprovedCNN + CIFAR10 Normalize)
// ---------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <torch/script.h>
#include <opencv2/opencv.hpp>

// CIFAR-10 Normalize değerleri
const float CIFAR10_MEAN[3] = {0.4914f, 0.4822f, 0.4465f}; // R, G, B
const float CIFAR10_STD[3] = {0.2470f, 0.2435f, 0.2616f};

torch::Tensor preprocess_image(const cv::Mat &img_bgr, int target_size)
{
    cv::Mat img;
    img_bgr.copyTo(img);

    cv::resize(img, img, cv::Size(target_size, target_size));
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);

    cv::Mat img_float;
    img.convertTo(img_float, CV_32F, 1.0f / 255.0f); // [0,1]

    // Kanal bazlı normalize
    {
        std::vector<cv::Mat> channels(3);
        cv::split(img_float, channels); // R, G, B

        for (int c = 0; c < 3; ++c)
        {
            channels[c] = (channels[c] - CIFAR10_MEAN[c]) / CIFAR10_STD[c];
        }

        cv::merge(channels, img_float);
    }

    auto tensor_image = torch::from_blob(
        img_float.data,
        {1, img_float.rows, img_float.cols, 3}, // [N, H, W, C]
        torch::TensorOptions().dtype(torch::kFloat32));

    tensor_image = tensor_image.permute({0, 3, 1, 2}); // [N, C, H, W]
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

        // exe hangi klasörde çalışıyorsa, path'ler O klasöre göre:
        const std::string model_path = "model_ts.pt";
        const std::string image_path = "test.jpg";

        // Model dosyasını kontrol et
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
        std::cout << "[OK] Model yüklendi.\n";

        module.to(torch::kCPU);
        module.eval();
        std::cout << "[OK] Model CPU'da ve eval modunda.\n";

        // Resmi oku
        cv::Mat img_bgr = cv::imread(image_path);
        if (img_bgr.empty())
        {
            std::cerr << "[HATA] Resim yuklenemedi! Beklenen yer: "
                      << image_path << "\n";
            std::cout << "Enter'a basip cikabilirsin...\n";
            std::cin.get();
            return -1;
        }

        std::cout << "[OK] Resim yuklendi. Boyut: "
                  << img_bgr.cols << "x" << img_bgr.rows << " (W x H)\n";

        int target_size = 64;
        torch::Tensor input_tensor = preprocess_image(img_bgr, target_size);
        std::cout << "[DEBUG] Input tensor shape: " << input_tensor.sizes() << "\n";

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

        std::cout << "[INFO] Inference calistiriliyor...\n";
        torch::Tensor output = run_inference(module, input_tensor);
        std::cout << "[DEBUG] Output tensor shape: " << output.sizes() << "\n";

        torch::Tensor probs = torch::softmax(output, 1);
        torch::Tensor pred_class = probs.argmax(1);

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
