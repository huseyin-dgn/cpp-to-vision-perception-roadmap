#include "preprocess_node.hpp"

#include <opencv2/imgproc.hpp>
#include <iostream>

// Constructor: config alır ve cihaz seçer
PreprocessNode::PreprocessNode(const PreprocessConfig &config)
    : config_(config)
{
    if (config_.device == "cuda" && torch::cuda::is_available())
    {
        device_ = torch::kCUDA;
        std::cout << "[PreprocessNode] CUDA kullanılacak.\n";
    }
    else
    {
        device_ = torch::kCPU;
        std::cout << "[PreprocessNode] CPU kullanılacak.\n";
    }
}

// Dış API: şu an direkt preprocess çağırıyoruz
torch::Tensor PreprocessNode::process(const ImageFrame &frame)
{
    return preprocess(frame);
}

// Asıl cv::Mat -> torch::Tensor dönüşümü
torch::Tensor PreprocessNode::preprocess(const ImageFrame &frame)
{
    std::cout << "[preprocess] Orijinal boyut: "
              << frame.image.cols << "x" << frame.image.rows << "\n";

    // 1) Boş görüntü kontrolü
    if (frame.image.empty())
    {
        std::cerr << "[preprocess] HATA: image boş, boş tensor döndürülüyor.\n";
        return torch::empty({0});
    }

    // 2) Resize
    cv::Mat resized;
    cv::resize(frame.image,
               resized,
               cv::Size(config_.input_width, config_.input_height));

    std::cout << "[preprocess] Resize sonrası boyut: "
              << resized.cols << "x" << resized.rows << "\n";

    // 3) BGR -> RGB
    cv::Mat rgb;
    cv::cvtColor(resized, rgb, cv::COLOR_BGR2RGB);

    // 4) float'a çevir ve [0, 1] aralığına getir
    cv::Mat float_img;
    rgb.convertTo(float_img, CV_32F, 1.0 / 255.0);

    const int height = float_img.rows;
    const int width = float_img.cols;
    const int channels = float_img.channels(); // 3

    auto options = torch::TensorOptions()
                       .dtype(torch::kFloat32)
                       .device(torch::kCPU); // ilk etapta CPU'da

    // 5) from_blob: OpenCV buffer'ını saran bir tensor (H, W, C)
    torch::Tensor tensor = torch::from_blob(
        float_img.data,
        {height, width, channels}, // [H, W, C]
        options);

    // 6) HWC -> CHW : [H, W, C] -> [C, H, W]
    tensor = tensor.permute({2, 0, 1});

    // 7) Batch dimension ekle: [C, H, W] -> [1, C, H, W]
    tensor = tensor.unsqueeze(0);

    // 8) Normalize (mean / std)
    if (config_.mean.size() == 3 && config_.std.size() == 3)
    {
        torch::Tensor mean = torch::tensor(config_.mean, options).view({1, 3, 1, 1});
        torch::Tensor std = torch::tensor(config_.std, options).view({1, 3, 1, 1});

        tensor = (tensor - mean) / std;
    }
    else
    {
        std::cout << "[preprocess] UYARI: mean/std boyutu 3 değil, normalize atlandı.\n";
    }

    // 9) Doğru cihaza taşı (CPU / CUDA)
    tensor = tensor.to(device_);

    // 10) from_blob OpenCV buffer'ına bağlı, güvenli olmak için clone
    tensor = tensor.clone();

    std::cout << "[preprocess] Tensor hazır. Shape: " << tensor.sizes()
              << ", device: " << (device_.is_cuda() ? "CUDA" : "CPU") << "\n";

    return tensor;
}
