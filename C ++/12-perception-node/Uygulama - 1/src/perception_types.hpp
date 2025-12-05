// Bu yapı bir header guard’dır.
// Aynı .hpp dosyası birden fazla kez include edilse bile, içindeki struct/class tanımlarının yalnızca bir kez derlenmesini sağlar.
// Mantık:

// İlk include’da makro tanımlı değil → dosya içeriği derlenir, makro tanımlanır.

// Sonrakilerde makro zaten tanımlıdır → dosya içeriği atlanır.

#ifndef PERCEPTION_TYPES_HPP
#define PERCEPTION_TYPES_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <chrono>

#include <opencv2/core.hpp>

// ImageFrame, tek bir kamera karesini temsil eden veri paketidir.
// İçinde:
// görüntü (cv::Mat),o frame’in ID’si,oluşturulma zamanı (timestamp),
// geldiği kamera (camera_name)
// birlikte tutulur.
// Bu sayede algılama pipeline’ına tek bir parametre ile hem piksel verisini
// hem de tüm bağlamsal bilgiyi gönderebilirim.

struct ImageFrame
{
    cv::Mat Image;

    // Sayaç tipinde taşma olmaması için kullanılıyor.
    // Negatife gitmeyecek ve bizim için ne kadar çalışırsa çalışsın sorun yaratmıcak bir yapı sağlıyor.
    std::uint64_t frame_id{0};

    // std::chrono, zaman ve süre hesaplamaya yarayan C++ standard kütüphanesidir.
    // steady_clock, geriye gitmeyen, sistem saatinden bağımsız, ölçüm için kullanılan bir saat tipidir.
    // timestamp, frame’in oluşturulduğu anı tutar; ileri aşamada latency ve senkronizasyon hesabı için kullanılır.
    std::chrono::steady_clock::time_point timestap{
        std::chrono::steady_clock::now()};

    // camera_name, bu frame’in hangi kameradan geldiğini taşır.
    // Multi-camera sistemlerde debugging ve senkronizasyon için kullanılır.
    std::string camera_name;

    // ImageFrame() = default;,
    // ImageFrame için “boş” bir constructor’ın var olmasını garanti eder.
    // Böylece hem ImageFrame frame; diyebilirim, hem de parametreli constructor’ı kullanabilirim.
    ImageFrame() = default;

    // Bu aslında kullanmak istediğimiz const. Amacı tek seferde const. oluşturmaktır.
    // Her seferinde aynı şeyi tanımlamıyoruz ve bize ciddi manada kolaylık sağlıyor.
    ImageFrame(const cv::Mat &img, std::uint64_t id, const std::string &cam)
        : Image(img),
          frame_id(id),
          timestap(std::chrono::steady_clock::now()),
          camera_name(cam)
    {
    }
};

// Tek bir algılanan nesneyi temsil eden veri yapısıdır.
// Modelin çıkardığı "bir obje" bu struct ile ifade edilir.
struct DetectedObject
{
    // Modelin sınıf kimliği (örn. 0 = person, 1 = car).
    // -1: Henüz sınıf atanmamış veya geçersiz.
    int class_id{-1};

    // İnsan okunabilir sınıf adı (örn. "person", "car").
    // Loglama, çizim ve dışa aktarma için kullanılır.
    std::string class_name;

    // Tespit güven skoru (0.0 - 1.0).
    // Modelin bu nesnenin varlığına ne kadar güvendiğini belirtir.
    float score{0.0f};

    // Bounding box bilgisi (piksel cinsinden).
    // (x, y): sol-üst köşe koordinatı
    // width:  kutunun genişliği
    // height: kutunun yüksekliği
    float x{0.0f};
    float y{0.0f};
    float width{0.0f};
    float height{0.0f}; // 'heigth' yazım hatası düzeltilmiştir

    // Nesne takibi için kullanılan ID.
    // Multi-frame takibi yapan algoritmalarda (SORT, DeepSORT, ByteTrack) kullanılır.
    // -1: Takip ID'si henüz atanmadı.
    int track_id{-1};
};

// Algılama (Perception) modülünün çalışma şeklini belirleyen
// konfigürasyon paketidir. Node bu struct'ı alarak kendi iç davranışını
// ayarlar ve tüm değişkenler dışarıdan kontrol edilebilir hale gelir.
struct PerceptionConfig
{
    // TorchScript model dosyasının yolu.
    // Ör: "../models/yolov8s.torchscript.pt"
    // Uygulama 1'de boş bırakılabilir.
    std::string model_path;

    // Node'un hangi cihazda çalışacağını belirtir.
    // "cpu" veya "cuda" olabilir.
    // Varsayılan cihaz "cpu" olarak seçilir çünkü daha güvenli ve evrenseldir.
    std::string device{"cpu"};

    // Modelin beklediği giriş boyutu (width x height).
    // YOLO gibi modeller genelde 640x640 kullanır.
    int input_width{640};
    int input_height{640};

    // Preprocess aşamasında kullanılacak normalizasyon için mean değerleri.
    // Varsayılan {0, 0, 0}: hiçbir offset uygulanmaz.
    std::vector<float> mean{0.0f, 0.0f, 0.0f};

    // Normalizasyon için kanal bazlı standart sapma değerleri.
    // Varsayılan {1, 1, 1}: bölme etkisizdir.
    std::vector<float> std{1.0f, 1.0f, 1.0f};

    // Modelin çıkardığı class_id değerini metin sınıf adlarına
    // dönüştürmek için kullanılan liste.
    // Ör: {"person", "car", "truck"} gibi.
    std::vector<std::string> class_names;
};

#endif