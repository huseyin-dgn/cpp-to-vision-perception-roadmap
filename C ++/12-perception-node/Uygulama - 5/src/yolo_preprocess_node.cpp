#include "yolo_preprocess_node.hpp"

#include <opencv2/imgproc.hpp>
#include <iostream>

YoloPreprocessNode::YoloPreprocessNode(const YoloPreprocessConfig& config)
    : config_(config)
{
    if (config_.device == "cuda" && torch::cuda::is_available())
    {
        device_ = torch::kCUDA;
        std::cout << "[YoloPreprocessNode] CUDA\n";
    }
    else
    {
        device_ = torch::kCPU;
        std::cout << "[YoloPreprocessNode] CPU\n";
    }
}

torch::Tensor YoloPreprocessNode::process(const ImageFrame& frame)
{
    return preprocess(frame);
}

torch::Tensor YoloPreprocessNode::preprocess(const ImageFrame& frame)
{
    if (frame.image.empty())
    {
        std::cerr << "[YoloPreprocessNode] empty frame\n";
        return torch::empty({0});
    }

    cv::Mat resized;
    cv::resize(frame.image,
               resized,
               cv::Size(config_.input_width, config_.input_height));

    cv::Mat rgb;
    cv::cvtColor(resized, rgb, cv::COLOR_BGR2RGB);

    cv::Mat float_img;
    rgb.convertTo(float_img, CV_32F, 1.0 / 255.0);

    int h = float_img.rows;
    int w = float_img.cols;
    int c = float_img.channels();

    auto options = torch::TensorOptions()
                       .dtype(torch::kFloat32)
                       .device(torch::kCPU);

    torch::Tensor tensor = torch::from_blob(
        float_img.data,
        {h, w, c},
        options
    );

    tensor = tensor.permute({2, 0, 1}); // CHW
    tensor = tensor.unsqueeze(0);       // NCHW

    tensor = tensor.to(device_);
    tensor = tensor.clone();

    return tensor;
}
