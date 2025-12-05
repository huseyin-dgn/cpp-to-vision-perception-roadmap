#include "perception_node.hpp"
#include <iostream>

#include <torch/script.h>
#include <torch/torch.h>

// Constructor
PerceptionNode::PerceptionNode(const PerceptionConfig &config)
    : config_(config)
{
    std::cout << "[PerceptionNode] Node oluşturuluyor...\n";

    // Cihaz seçimi
    if (config_.device == "cuda" && torch::cuda::is_available())
    {
        device_ = torch::kCUDA;
        std::cout << "[PerceptionNode] CUDA kullanılacak.\n";
    }
    else
    {
        device_ = torch::kCPU;
        std::cout << "[PerceptionNode] CPU kullanılacak.\n";
    }

    // Model yükleme
    if (!config_.model_path.empty())
    {
        std::cout << "[PerceptionNode] Model yükleniyor: "
                  << config_.model_path << "\n";
        loadModel(config_.model_path);
    }
    else
    {
        std::cout << "[PerceptionNode] Model path boş, dummy mod aktif.\n";
        model_loaded_ = false;
    }
}

// Dummy model yükleme
void PerceptionNode::loadModel(const std::string &path)
{
    try
    {
        model_ = torch::jit::load(path);
        model_.to(device_);
        model_loaded_ = true;

        std::cout << "[PerceptionNode] Model başarıyla yüklendi.\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "[PerceptionNode] Model yüklenemedi: " << e.what() << "\n";
        model_loaded_ = false;
    }
}

// Uygulama 1 — preprocess (dummy)
torch::Tensor PerceptionNode::preprocess(const ImageFrame &frame)
{
    std::cout << "[preprocess] Frame alındı. Boyut: "
              << frame.image.cols << "x" << frame.image.rows << "\n";

    std::cout << "[preprocess] Uygulama 1 modunda çalışıyor: dummy tensor döndürülüyor.\n";

    return torch::rand({1, 3, 640, 640});
}

// Uygulama 1 — inference (dummy)
torch::Tensor PerceptionNode::inference(const torch::Tensor &input)
{
    std::cout << "[inference] Girilen tensor shape: " << input.sizes() << "\n";

    if (!model_loaded_)
    {
        std::cout << "[inference] Model yüklenmemiş. Dummy output döndürülüyor.\n";
        return torch::rand({1, 1});
    }

    torch::NoGradGuard no_grad;

    auto output = model_.forward({input}).toTensor();

    std::cout << "[inference] Model çıktısı alındı.\n";

    return output;
}

// Uygulama 1 — postprocess (dummy)
std::vector<DetectedObject> PerceptionNode::postprocess(
    const ImageFrame &frame,
    const torch::Tensor &output)
{
    std::cout << "[postprocess] Dummy postprocess çalışıyor. output shape: "
              << output.sizes() << "\n";

    // Tek adet sahte nesne
    DetectedObject obj;
    obj.class_id = 0;
    obj.class_name = "dummy_object";
    obj.score = 0.9f;
    obj.x = 100;
    obj.y = 120;
    obj.width = 50;
    obj.height = 60;

    return {obj};
}

// Ana API — process()
std::vector<DetectedObject> PerceptionNode::process(const ImageFrame &frame)
{
    std::cout << "[process] === Algılama pipeline başlatıldı ===\n";

    auto input_tensor = preprocess(frame);
    auto output = inference(input_tensor);
    auto detections = postprocess(frame, output);

    std::cout << "[process] === Pipeline tamamlandı ===\n";

    return detections;
}
