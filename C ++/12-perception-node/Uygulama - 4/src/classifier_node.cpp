#include "classifier_node.hpp"

#include <iostream>

Cifar10ClassifierNode::Cifar10ClassifierNode(const ClassifierConfig& config)
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
        model_loaded_ = true;
        std::cout << "[Cifar10ClassifierNode] Model yüklendi: "
                  << config_.model_path << "\n";
    }
    catch (const c10::Error& e)
    {
        std::cerr << "[Cifar10ClassifierNode] Model yüklenemedi: "
                  << e.what() << "\n";
        model_loaded_ = false;
    }
}

bool Cifar10ClassifierNode::predict(const torch::Tensor& input,
                                    int& out_class_id,
                                    std::string& out_class_name,
                                    float& out_score,
                                    bool xray_mode)
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

        if (xray_mode)
        {
            std::cout << "[XRAY-CPP] Logits shape: "
                      << logits.sizes() << "\n";

            int num_classes = logits.size(1);
            int print_count = std::min(num_classes, 10);
            std::cout << "[XRAY-CPP] İlk " << print_count << " logits:\n";
            for (int i = 0; i < print_count; ++i)
            {
                float val = logits[0][i].item<float>();
                std::string name = "UNKNOWN";
                if (i >= 0 &&
                    i < static_cast<int>(config_.class_names.size()))
                {
                    name = config_.class_names[static_cast<std::size_t>(i)];
                }
                std::cout << "  class " << i
                          << " (" << name << "): "
                          << val << "\n";
            }
        }

        torch::Tensor probs = torch::softmax(logits, 1);

        if (xray_mode)
        {
            auto topk = probs.topk(5, 1);
            torch::Tensor top_vals = std::get<0>(topk);
            torch::Tensor top_idx  = std::get<1>(topk);

            std::cout << "[XRAY-CPP] Top-5 olasılıklar:\n";
            for (int k = 0; k < 5; ++k)
            {
                int idx = top_idx[0][k].item<int>();
                float val = top_vals[0][k].item<float>();

                std::string name = "UNKNOWN";
                if (idx >= 0 &&
                    idx < static_cast<int>(config_.class_names.size()))
                {
                    name = config_.class_names[static_cast<std::size_t>(idx)];
                }

                std::cout << "  #" << (k + 1)
                          << ": id=" << idx
                          << ", name=" << name
                          << ", score=" << val << "\n";
            }
        }

        auto max_result = probs.max(1);
        torch::Tensor max_values  = std::get<0>(max_result);
        torch::Tensor max_indices = std::get<1>(max_result);

        out_class_id = max_indices.item<int>();
        out_score    = max_values.item<float>();

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
    catch (const c10::Error& e)
    {
        std::cerr << "[Cifar10ClassifierNode] Inference hatası: "
                  << e.what() << "\n";
        return false;
    }
}
