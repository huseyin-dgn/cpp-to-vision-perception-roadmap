#include "preprocess_node.hpp"

#include <opencv2/imgproc.hpp>
#include <iostream>

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

torch::Tensor PreprocessNode::process(const ImageFrame &frame)
{
    return preprocess(frame);
}

torch::Tensor PreprocessNode::preprocess(const ImageFrame &frame)
{
    if (frame.image.empty())
    {
        std::cerr << "[PreprocessNode] HATA: Frame içindeki image boş.\n";
        return torch::empty({0});
    }

    std::cout << "[PreprocessNode] Orijinal boyut: "
              << frame.image.cols << "x" << frame.image.rows << "\n";

    cv::Mat resized;
    cv::resize(frame.image,
               resized,
               cv::Size(config_.input_width, config_.input_height));

    std::cout << "[PreprocessNode] Resize sonrası boyut: "
              << resized.cols << "x" << resized.rows << "\n";

    cv::Mat rgb;
    cv::cvtColor(resized, rgb, cv::COLOR_BGR2RGB);

    cv::Mat float_img;
    rgb.convertTo(float_img, CV_32F, 1.0 / 255.0);

    const int height = float_img.rows;
    const int width = float_img.cols;
    const int channels = float_img.channels();

    auto options = torch::TensorOptions()
                       .dtype(torch::kFloat32)
                       .device(torch::kCPU);

    torch::Tensor tensor = torch::from_blob(
        float_img.data,
        {height, width, channels}, // [H, W, C]
        options);

    tensor = tensor.permute({2, 0, 1});

    tensor = tensor.unsqueeze(0);

    // 7) Normalize (mean / std) - CIFAR-10 değerleri
    if (config_.mean.size() == 3 && config_.std.size() == 3)
    {
        torch::Tensor mean = torch::tensor(config_.mean, options).view({1, 3, 1, 1});
        torch::Tensor std = torch::tensor(config_.std, options).view({1, 3, 1, 1});

        tensor = (tensor - mean) / std;
    }
    else
    {
        std::cout << "[PreprocessNode] UYARI: mean/std boyutu 3 değil, normalize atlandı.\n";
    }
    tensor = tensor.to(device_);

    tensor = tensor.clone();

    std::cout << "[PreprocessNode] Tensor hazır. Shape: " << tensor.sizes()
              << ", device: " << (device_.is_cuda() ? "CUDA" : "CPU") << "\n";

    return tensor;
}