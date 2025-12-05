#ifndef CLASSIFIER_NODE_HPP
#define CLASSIFIER_NODE_HPP

#include <torch/script.h>
#include <string>
#include <vector>

struct ClassifierConfig
{
    std::string model_path;
    std::string device{"cpu"};
    std::vector<std::string> class_names;
};

class Cifar10ClassifierNode
{
public:
    explicit Cifar10ClassifierNode(const ClassifierConfig &config);

    bool predict(const torch::Tensor &input,
                 int &out_class_id,
                 std::string &out_class_name,
                 float &out_score);

private:
    ClassifierConfig config_;
    torch::Device device_{torch::kCPU};
    torch::jit::script::Module model_;
    bool model_loaded_{false};
};

#endif