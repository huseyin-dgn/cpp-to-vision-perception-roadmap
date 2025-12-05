#include "classifier_node.hpp"

#include <iostream>

Cifar10ClassifierNode::Cifar10ClassifierNode(const ClassifierConfig &config)
    : config_(config)
{
    if (config_.device == "cuda" && torch::cuda::is_available())
    {
        device_ = torch::kCUDA;
        std::cout << "[Cifar10ClassifierNode] CUDA kullanılacak.\n";
    }
    else
    {
        device_ = torch::kCPU;
        std::cout << "[Cifar10ClassifierNode] CPU kullanılacak.\n";
    }

    try
    {
        model_ = torch::jit::load(config_.model_path, device_);
        model_.eval();
        model_loaded_{true};
        std::cout << "[Cifar10ClassifierNode] Model yüklendi: "
                  << config_.model_path << "\n";
    }
    catch (const c10::Error &e)
    {
        std::cerr << "[Cifar10ClassifierNode] Model yüklenemedi: "
                  << e.what() << "\n";
        model_loaded_ = false;
    }
}

bool Cifar10ClassifierNode::predict(const torch::Tensor &input,
                                    int &out_class_id,
                                    std::string &out_class_name,
                                    float &out_score)
{
    if (!model_loaded_)
    {
        std::cerr << "[Cifar10ClassifierNode] HATA: Model yüklü değil.\n";
        return false;
    }

    if (!input.defined() || input.numel() == 0)
    {
        std::cerr << "[Cifar10ClassifierNode] HATA: Geçersiz input tensor.\n";
        return false;
    }
    torch::Tensor tensor = input.to(device_);

    try
    {
        torch::NoGradGuard no_grad;

        std::vector<torch::jit::IValue> inputs;
        inputs.push_back(tensor);

        torch::Tensor logits = model_.forward(inputs).toTensor();

        if (logits.dim() != 2)
        {
            std::cerr << "[Cifar10ClassifierNode] Beklenen logits shape [1, num_classes], "
                      << "gelen: " << logits.sizes() << "\n";
            return false;
        }

        // Softmax ile olasılık
        torch::Tensor probs = torch::softmax(logits, 1);

        // En yüksek skor ve index
        auto max_result = probs.max(1);
        torch::Tensor max_values = std::get<0>(max_result);
        torch::Tensor max_indices = std::get<1>(max_result);

        out_class_id = max_indices.item<int>();
        out_score = max_values.item<float>();

        if (out_class_id >= 0 &&
            out_class_id < static_cast<int>(config_.class_names.size()))
        {
            out_class_name = config_.class_names[static_cast<std::size_t>(out_class_id)];
        }
        else
        {
            out_class_name = "UNKNOWN";
        }

        return true;
    }
    catch (const c10::Error &e)
    {
        std::cerr << "[Cifar10ClassifierNode] Inference hatası: "
                  << e.what() << "\n";
        return false;
    }
}