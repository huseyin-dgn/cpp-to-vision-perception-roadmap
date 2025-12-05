#ifndef PREPROCESS_NODE_HPP
#define PREPROCESS_NODE_HPP

#include "frame_types.hpp"

#include <torch/torch.h>
#include <string>
#include <vector>

struct PreprocessConfig
{
    int input_width{32};
    int input_height{32};

    std::vector<float> mean{0.4914f, 0.4822f, 0.4465f};
    std::vector<float> std{0.2470f, 0.2435f, 0.2616f};

    std::string device{"cpu"}; // "cpu" veya "cuda"
};

class PreprocessNode
{
public:
    explicit PreprocessNode(const PreprocessConfig &config);

    torch::Tensor process(const ImageFrame &frame);

private:
    torch::Tensor preprocess(const ImageFrame &frame);

private:
    PreprocessConfig config_;
    torch::Device device_{torch::kCPU};
};

#endif
