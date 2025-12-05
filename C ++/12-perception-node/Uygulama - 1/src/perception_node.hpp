#ifndef PERCEPTION_NODE_HPP
#define PERCEPTION_NODE_HPP

// Bu header, algılama (perception) modülünün asıl "node" sınıfını tanımlar.
// Amaç: Algılama ile ilgili tüm işlemleri (preprocess, inference, postprocess)
// tek bir C++ sınıfının içine toplamak ve dışarıya temiz bir API sunmak.

#include "perception_types.hpp"

#include <torch/script.h> // torch::jit::script::Module, torch::Tensor, torch::Device
#include <vector>
#include <string>

// PerceptionNode:
//
// - Input  : ImageFrame (tek bir kamera karesi + bağlam bilgisi)
// - Output : std::vector<DetectedObject> (tespit edilen nesnelerin listesi)
//
// Dışarıdan sadece process(frame) fonksiyonu çağrılır.
// Detaylar (model yükleme, preprocess, inference, postprocess) sınıf içinde tutulur.
class PerceptionNode
{
public:
    // Constructor:
    // - config: node'un çalışma şeklini belirleyen ayar paketi
    //           (model path, device, input size, mean/std, class_names, vs.)
    explicit PerceptionNode(const PerceptionConfig &config);

    // Ana API:
    // - frame alır
    // - preprocess(frame) → inference(tensor) → postprocess(frame, output)
    //   adımlarını sırasıyla çalıştırır
    // - tespit edilen nesneleri DetectedObject listesi olarak döndürür
    std::vector<DetectedObject> process(const ImageFrame &frame);

private:
    // Model yükleme fonksiyonu:
    // - TorchScript model dosyasını verilen yoldan yükler
    // - device_ üzerine taşır (CPU/CUDA)
    // - model_loaded_ bayrağını günceller
    void loadModel(const std::string &path);

    // Preprocess:
    // - ImageFrame içindeki cv::Mat görüntüyü alır
    // - Gerekli resize / normalize işlemlerini yaparak
    //   torch::Tensor formatına çevirir
    // - Uygulama 1'de dummy tensor döndüreceğiz, ileride gerçek implementasyon yazılacak
    torch::Tensor preprocess(const ImageFrame &frame);

    // Inference:
    // - preprocess'ten gelen input tensor'ü model üzerinde çalıştırır
    // - TorchScript modeline forward çağrısı yapar
    // - Uygulama 1'de model yüklü değilse dummy çıktı döndüreceğiz
    torch::Tensor inference(const torch::Tensor &input);

    // Postprocess:
    // - Model çıktısını (output tensor) alır
    // - Bounding box, class_id, score gibi bilgileri decode eder
    // - DetectedObject listesi oluşturur
    // - Uygulama 1'de dummy bir nesne üretip geri döndüreceğiz
    std::vector<DetectedObject> postprocess(const ImageFrame &frame,
                                            const torch::Tensor &output);

private:
    // Node konfigürasyonunu saklıyoruz
    PerceptionConfig config_;

    // TorchScript model nesnesi
    torch::jit::script::Module model_;

    // Kullanılan cihaz (CPU veya CUDA)
    torch::Device device_{torch::kCPU};

    // Model gerçekten başarıyla yüklendi mi?
    bool model_loaded_{false};
};

#endif // PERCEPTION_NODE_HPP
