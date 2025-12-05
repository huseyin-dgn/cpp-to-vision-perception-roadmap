#ifndef PREPROCESS_NODE_HPP
#define PREPROCESS_NODE_HPP

#include "frame_types.hpp"

#include <torch/torch.h>
#include <string>
#include <vector>

// Preprocess ayarları (giriş boyutu, normalize parametreleri, cihaz)
struct PreprocessConfig
{
    int input_width{640};
    int input_height{640};

    std::vector<float> mean{0.485f, 0.456f, 0.406f};
    std::vector<float> std{0.229f, 0.224f, 0.225f};

    std::string device{"cpu"}; // "cpu" veya "cuda"
};

// Sadece preprocess işini yapan node
class PreprocessNode
{
public:
    explicit PreprocessNode(const PreprocessConfig &config);

    // Dışarıya açılan API: ImageFrame -> Tensor
    torch::Tensor process(const ImageFrame &frame);

private:
    // Asıl işi yapan iç fonksiyon
    torch::Tensor preprocess(const ImageFrame &frame);

private:
    PreprocessConfig config_;
    torch::Device device_{torch::kCPU};
};

#endif // PREPROCESS_NODE_HPP
