#ifndef YOLO_PREPROCESS_NODE_HPP
#define YOLO_PREPROCESS_NODE_HPP

#include "frame_types.hpp"

#include <torch/torch.h>
#include <string>

struct YoloPreprocessConfig
{
    int input_width{640};
    int input_height{640};
    std::string device{"cpu"}; // "cpu" veya "cuda"
};

class YoloPreprocessNode
{
public:
    explicit YoloPreprocessNode(const YoloPreprocessConfig& config);

    torch::Tensor process(const ImageFrame& frame);

private:
    torch::Tensor preprocess(const ImageFrame& frame);

private:
    YoloPreprocessConfig config_;
    torch::Device device_{torch::kCPU};
};

#endif // YOLO_PREPROCESS_NODE_HPP
