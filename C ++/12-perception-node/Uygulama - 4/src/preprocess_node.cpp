#include "preprocess_node.hpp"

#include <opencv2/imgproc.hpp>
#include <iostream>

PreprocessNode::PreprocessNode(const PreprocessConfig& config)
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

torch::Tensor PreprocessNode::process(const ImageFrame& frame, bool xray_mode)
{
    return preprocess(frame, xray_mode);
}

torch::Tensor PreprocessNode::preprocess(const ImageFrame& frame, bool xray_mode)
{
    if (frame.image.empty())
    {
        std::cerr << "[PreprocessNode] HATA: Frame image boş.\n";
        return torch::empty({0});
    }

    if (xray_mode)
    {
        std::cout << "[XRAY-CPP] Orijinal boyut: "
                  << frame.image.cols << "x" << frame.image.rows << "\n";
    }

    cv::Mat resized;
    cv::resize(frame.image,
               resized,
               cv::Size(config_.input_width, config_.input_height));

    if (xray_mode)
    {
        std::cout << "[XRAY-CPP] Resize sonrası boyut: "
                  << resized.cols << "x" << resized.rows << "\n";
    }

    cv::Mat rgb;
    cv::cvtColor(resized, rgb, cv::COLOR_BGR2RGB);

    cv::Mat float_img;
    rgb.convertTo(float_img, CV_32F, 1.0 / 255.0);

    int height   = float_img.rows;
    int width    = float_img.cols;
    int channels = float_img.channels();

    auto options = torch::TensorOptions()
                       .dtype(torch::kFloat32)
                       .device(torch::kCPU);

    // HWC tensor
    torch::Tensor tensor = torch::from_blob(
        float_img.data,
        {height, width, channels},
        options
    );

    if (xray_mode)
    {
        std::cout << "[XRAY-CPP] Tensor (HWC) shape: "
                  << tensor.sizes() << "\n";
    }

    // CHW
    tensor = tensor.permute({2, 0, 1});
    if (xray_mode)
    {
        std::cout << "[XRAY-CPP] Tensor (CHW) shape: "
                  << tensor.sizes() << "\n";
    }

    // NCHW
    tensor = tensor.unsqueeze(0);
    if (xray_mode)
    {
        std::cout << "[XRAY-CPP] Tensor (NCHW) shape: "
                  << tensor.sizes() << "\n";
    }

    // Normalize
    if (config_.mean.size() == 3 && config_.std.size() == 3)
    {
        torch::Tensor mean = torch::tensor(config_.mean, options).view({1, 3, 1, 1});
        torch::Tensor std  = torch::tensor(config_.std,  options).view({1, 3, 1, 1});
        tensor = (tensor - mean) / std;
    }

    tensor = tensor.to(device_);
    tensor = tensor.clone();

    if (xray_mode)
    {
        torch::Tensor cpu_tensor = tensor.to(torch::kCPU);
        float r = cpu_tensor[0][0][0][0].item<float>();
        float g = cpu_tensor[0][1][0][0].item<float>();
        float b = cpu_tensor[0][2][0][0].item<float>();

        std::cout << "[XRAY-CPP] (0,0) normalized RGB: "
                  << "R=" << r << ", G=" << g << ", B=" << b << "\n";
    }

    return tensor;
}
