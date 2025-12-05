#ifndef CLASSIFIER_NODE_HPP
#define CLASSIFIER_NODE_HPP

#include <torch/script.h>
#include <string>
#include <vector>

// CIFAR-10 sınıflandırıcı node için config
struct ClassifierConfig
{
    std::string model_path;               // TorchScript model yolu
    std::string device{"cpu"};            // "cpu" veya "cuda"
    std::vector<std::string> class_names; // CIFAR-10 etiketleri
};

// TorchScript CIFAR-10 CNN modeliyle inference yapan node
class Cifar10ClassifierNode
{
public:
    explicit Cifar10ClassifierNode(const ClassifierConfig& config);

    bool predict(const torch::Tensor& input,
                 int& out_class_id,
                 std::string& out_class_name,
                 float& out_score,
                 bool xray_mode = false);

private:
    ClassifierConfig config_;
    torch::Device device_{torch::kCPU};
    torch::jit::script::Module model_;
    bool model_loaded_{false};
};

#endif // CLASSIFIER_NODE_HPP
