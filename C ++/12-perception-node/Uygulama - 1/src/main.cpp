#include <iostream>
#include <opencv2/opencv.hpp>

#include "perception_types.hpp"
#include "perception_node.hpp"

int main()
{
    // 1) Test için bir resim yükle
    // Bu dosyanın, çalıştırdığın exe ile aynı klasörde
    // veya uygun relative path ile erişilebilir olması gerekir.
    cv::Mat img = cv::imread("test.jpg");
    if (img.empty())
    {
        std::cerr << "[main] test.jpg yüklenemedi. "
                  << "Çalışma dizinini ve dosya yolunu kontrol et.\n";
        return 1;
    }

    // 2) ImageFrame oluştur
    // Amaç: tek bir kamera karesini (görüntü + id + kamera adı)
    // tek bir struct içinde temsil etmek.
    ImageFrame frame(
        img,           // görüntü
        1,             // frame_id
        "front_camera" // kamera adı
    );

    // 3) PerceptionConfig doldur
    // Bu config, PerceptionNode'un nasıl çalışacağını belirler.
    PerceptionConfig config;

    // Şimdilik model_path boş kalsın: Uygulama 1'de dummy inference kullanıyoruz.
    config.model_path = ""; // İleride: "yolov8s.torchscript.pt" vb. vereceğiz.

    // Cihaz seçimi: "cpu" veya "cuda"
    config.device = "cpu";

    // Modelin beklediği giriş boyutu (Uygulama 1'de sadece log için kullanıyoruz)
    config.input_width = 640;
    config.input_height = 640;

    // Normalize parametreleri (şimdilik nötr bırakıyoruz)
    config.mean = {0.0f, 0.0f, 0.0f};
    config.std = {1.0f, 1.0f, 1.0f};

    // Sınıf isimlerini şimdiden doldurmak istersen:
    // Dummy bir örnek set verebiliriz.
    config.class_names = {
        "dummy_object" // class_id = 0 için
    };

    // 4) PerceptionNode oluştur
    // Amaç: Algılama ile ilgili tüm işlemleri (preprocess, inference, postprocess)
    // tek bir sınıfın içine toplamak.
    PerceptionNode perception(config);

    // 5) process() çağır
    // Bu çağrı, içeride şu akışı tetikler:
    // preprocess(frame) -> inference(tensor) -> postprocess(frame, output)
    auto detections = perception.process(frame);

    // 6) Sonuçları ekrana yazdır
    std::cout << "\n[main] Dönüşte gelen tespitler:\n";

    if (detections.empty())
    {
        std::cout << "  (Tespit yok)\n";
    }
    else
    {
        for (const auto &obj : detections)
        {
            std::cout << "  class_id: " << obj.class_id
                      << ", name: " << obj.class_name
                      << ", score: " << obj.score
                      << ", bbox: (" << obj.x << ", " << obj.y
                      << ", " << obj.width << ", " << obj.height
                      << "), track_id: " << obj.track_id
                      << "\n";
        }
    }

    return 0;
}
