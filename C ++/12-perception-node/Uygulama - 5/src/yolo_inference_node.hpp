#ifndef YOLO_INFERENCE_NODE_HPP
#define YOLO_INFERENCE_NODE_HPP

#include "detection_types.hpp"

#include <torch/script.h>
#include <string>

struct YoloInferenceConfig
{
    std::string model_path;
    std::string device{"cpu"}; // "cpu" veya "cuda"
    float score_threshold{0.25f};
};

class YoloInferenceNode
{
public:
    explicit YoloInferenceNode(const YoloInferenceConfig& config);

    DetectionList infer(const torch::Tensor& input,
                        int orig_width,
                        int orig_height);

private:
    YoloInferenceConfig config_;
    torch::Device device_{torch::kCPU};
    torch::jit::script::Module model_;
    bool model_loaded_{false};
};

#endif // YOLO_INFERENCE_NODE_HPP
