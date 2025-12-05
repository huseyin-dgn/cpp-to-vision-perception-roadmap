#include <iostream>
#include <opencv2/opencv.hpp>

#include "frame_types.hpp"
#include "cifar10_labels.hpp"
#include "preprocess_node.hpp"
#include "classifier_node.hpp"

int main(int argc, char **argv)
{
    // 1) Komut satırından resim yolu al
    std::string image_path = "test.png"; // varsayılan
    if (argc >= 2)
    {
        image_path = argv[1];
    }

    std::cout << "[main] Kullanılacak resim: " << image_path << "\n";

    // 2) Görüntüyü yükle
    cv::Mat img = cv::imread(image_path);
    if (img.empty())
    {
        std::cerr << "[main] HATA: Resim yüklenemedi. Yol doğru mu?\n";
        return 1;
    }

    std::cout << "[main] Resim yüklendi. Orijinal boyut: "
              << img.cols << "x" << img.rows << "\n";

    // 3) ImageFrame oluştur
    ImageFrame frame(img, 1, "file:" + image_path);

    // 4) PreprocessNode config ve oluşturma
    PreprocessConfig pre_cfg;
    pre_cfg.input_width = 32;
    pre_cfg.input_height = 32;
    pre_cfg.mean = {0.4914f, 0.4822f, 0.4465f};
    pre_cfg.std = {0.2470f, 0.2435f, 0.2616f};
    pre_cfg.device = "cpu"; // CUDA istersen "cuda" yap

    PreprocessNode preprocess_node(pre_cfg);

    // 5) Frame -> Tensor
    torch::Tensor input_tensor = preprocess_node.process(frame);
    if (!input_tensor.defined() || input_tensor.numel() == 0)
    {
        std::cerr << "[main] HATA: Preprocess başarısız, boş tensor.\n";
        return 1;
    }

    std::cout << "[main] Preprocess sonrası tensor shape: "
              << input_tensor.sizes() << "\n";

    // 6) Classifier config
    ClassifierConfig clf_cfg;
    clf_cfg.model_path = "../models/cifar10_cnn_scripted.pt"; // build dizinine göre ayarla
    clf_cfg.device = "cpu";                                   // CUDA istersen "cuda"
    clf_cfg.class_names = CIFAR10_LABELS;

    Cifar10ClassifierNode classifier_node(clf_cfg);

    // 7) Tahmin al
    int class_id = -1;
    std::string class_name;
    float score = 0.0f;

    bool ok = classifier_node.predict(input_tensor, class_id, class_name, score);
    if (!ok)
    {
        std::cerr << "[main] HATA: Tahmin yapılamadı.\n";
        return 1;
    }

    std::cout << "-----------------------------\n";
    std::cout << "[RESULT] class_id   = " << class_id << "\n";
    std::cout << "[RESULT] class_name = " << class_name << "\n";
    std::cout << "[RESULT] score      = " << score << "\n";
    std::cout << "-----------------------------\n";

    return 0;
}