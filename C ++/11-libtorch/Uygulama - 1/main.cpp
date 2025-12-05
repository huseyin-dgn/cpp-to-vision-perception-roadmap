#include <iostream>
#include <fstream>
#include <torch/script.h>

int main()
{
    try
    {
        const std::string model_path = "model_ts.pt";

        std::cout << "[INFO] Program başladı.\n";
        std::cout << "[INFO] Beklenen model yolu: " << model_path << "\n";

        // 0) Dosya gerçekten var mı kontrol ediyorum
        {
            std::ifstream f(model_path);
            if (!f.good())
            {
                std::cerr << "[HATA] model_ts.pt bulundu MU? -> HAYIR\n";
                std::cerr << "[HATA] model_ts.pt dosyasını exe ile aynı klasöre koymalısın.\n";
                std::cout << "Çıkmak için Enter'a bas...\n";
                std::cin.get();
                return -1;
            }
            else
            {
                std::cout << "[OK] model_ts.pt bulundu.\n";
            }
        }

        // 1) Modeli yükle
        torch::jit::script::Module module = torch::jit::load(model_path);
        std::cout << "[OK] Model yüklendi.\n";

        // 2) Cihaz (CPU)
        torch::Device device(torch::kCPU);
        module.to(device);
        module.eval();
        std::cout << "[OK] Model CPU'ya taşındı ve eval moduna alındı.\n";

        // 3) Dummy input
        torch::Tensor input = torch::randn({1, 10}, torch::TensorOptions().device(device));
        std::cout << "[OK] Dummy input olusturuldu. Shape: " << input.sizes() << "\n";

        // 4) Forward
        std::vector<torch::jit::IValue> inputs;
        inputs.push_back(input);

        torch::Tensor output = module.forward(inputs).toTensor();

        std::cout << "[OK] Forward bitti.\n";
        std::cout << "Input shape : " << input.sizes() << std::endl;
        std::cout << "Output shape: " << output.sizes() << std::endl;
        std::cout << "Output tensor:\n"
                  << output << std::endl;
    }
    catch (const c10::Error &e)
    {
        std::cerr << "[EXCEPTION] LibTorch hata fırlattı:\n"
                  << e.what() << std::endl;
        std::cout << "Çıkmak için Enter'a bas...\n";
        std::cin.get();
        return -1;
    }

    std::cout << "Program bitti. Çıkmak için Enter'a bas...\n";
    std::cin.get();
    return 0;
}
