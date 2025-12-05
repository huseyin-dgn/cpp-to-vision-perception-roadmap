#include <iostream>
#include <opencv2/opencv.hpp>

#include "frame_types.hpp"
#include "preprocess_node.hpp"

int main()
{
    // 1) Test görüntüsünü yükle
    cv::Mat img = cv::imread("test.jpg");
    if (img.empty())
    {
        std::cerr << "[main] test.jpg yüklenemedi. "
                  << "Çalışma dizinini ve dosya yolunu kontrol et.\n";
        return 1;
    }

    std::cout << "[main] test.jpg yüklendi. Boyut: "
              << img.cols << "x" << img.rows << "\n";

    // 2) ImageFrame oluştur
    ImageFrame frame(img, 1, "file:test.jpg");

    // 3) PreprocessConfig ayarla
    PreprocessConfig config;
    config.input_width = 640;
    config.input_height = 640;

    // ImageNet / PyTorch standart normalize
    config.mean = {0.485f, 0.456f, 0.406f};
    config.std = {0.229f, 0.224f, 0.225f};

    config.device = "cpu"; // CUDA kullanacaksan "cuda" yap

    // 4) Node oluştur
    PreprocessNode node(config);

    // 5) Preprocess çalıştır
    torch::Tensor input_tensor = node.process(frame);

    if (input_tensor.numel() == 0)
    {
        std::cerr << "[main] Boş tensor döndü, preprocess başarısız.\n";
        return 1;
    }

    std::cout << "[main] Final tensor shape: " << input_tensor.sizes() << "\n";
    std::cout << "[main] bitti.\n";

    return 0;
}
