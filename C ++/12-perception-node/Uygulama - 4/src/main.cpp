#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

#include "frame_types.hpp"
#include "cifar10_labels.hpp"
#include "preprocess_node.hpp"
#include "classifier_node.hpp"

int main(int argc, char** argv)
{
    std::string image_path = "test.png";
    bool xray_mode = false;

    // Kullanım: cifar10_app [--xray] image_path
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "--xray")
        {
            xray_mode = true;
        }
        else
        {
            image_path = arg;
        }
    }

    std::cout << "[main] Resim yolu: " << image_path << "\n";
    std::cout << "[main] X-Ray modu: " << (xray_mode ? "AÇIK" : "KAPALI") << "\n";

    cv::Mat img = cv::imread(image_path);
    if (img.empty())
    {
        std::cerr << "[main] HATA: Resim yüklenemedi.\n";
        return 1;
    }

    std::cout << "[main] Orijinal boyut: "
              << img.cols << "x" << img.rows << "\n";

    ImageFrame frame(img, 1, "file:" + image_path);

    PreprocessConfig pre_cfg;
    pre_cfg.input_width  = 32;
    pre_cfg.input_height = 32;
    pre_cfg.mean = {0.4914f, 0.4822f, 0.4465f};
    pre_cfg.std  = {0.2470f, 0.2435f, 0.2616f};
    pre_cfg.device = "cpu"; // İstersen "cuda"

    PreprocessNode preprocess_node(pre_cfg);

    torch::Tensor input_tensor = preprocess_node.process(frame, xray_mode);
    if (!input_tensor.defined() || input_tensor.numel() == 0)
    {
        std::cerr << "[main] HATA: Preprocess başarısız.\n";
        return 1;
    }

    std::cout << "[main] Preprocess sonrası tensor shape: "
              << input_tensor.sizes() << "\n";

    ClassifierConfig clf_cfg;
    clf_cfg.model_path  = "../models/cifar10_cnn_scripted.pt"; // build dizinine göre ayarla
    clf_cfg.device      = "cpu"; // veya "cuda"
    clf_cfg.class_names = CIFAR10_LABELS;

    Cifar10ClassifierNode classifier_node(clf_cfg);

    int class_id = -1;
    std::string class_name;
    float score = 0.0f;

    bool ok = classifier_node.predict(input_tensor,
                                      class_id,
                                      class_name,
                                      score,
                                      xray_mode);
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
