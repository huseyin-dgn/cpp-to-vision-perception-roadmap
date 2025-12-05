/*
🧩 SORU 8 — CANLI AKIŞTA FPS ÖLÇ VE GÖSTER

Görevlerin:

1) Kamerayı aç:
      cv::VideoCapture cap(0);

2) Kamera açılmazsa programdan çık.

3) Sonsuz döngü başlat:
      while (true) { ... }

4) Döngü içinde:

   - Döngü başında zaman sayacını al:
        int64 t1 = cv::getTickCount();

   - Kameradan frame oku, boşsa break.

   - Gerekirse frame üzerinde basit bir işlem yap (şimdilik şart değil).

   - Döngünün sonunda tekrar zaman sayacını al:
        int64 t2 = cv::getTickCount();

   - Geçen süreyi saniye cinsinden hesapla:
        double deltaTime = (t2 - t1) / cv::getTickFrequency();

   - FPS'yi hesapla:
        double fps = 1.0 / deltaTime;

5) FPS değerini string'e çevirip, frame'in üzerine yaz:
      cv::putText(
          frame,
          "FPS: " + std::to_string(fps),
          cv::Point(10, 30),           // sol üst köşe civarı
          cv::FONT_HERSHEY_SIMPLEX,
          0.8,
          cv::Scalar(0, 255, 0),       // yazı rengi (yeşil)
          2
      );

6) Frame'i "Kamera + FPS" penceresinde göster.

7) 'q' veya 'Q' basılırsa döngüden çık.

8) cap.release() + destroyAllWindows() ile bitir.

Aşağıdaki main fonksiyonunu bu adımlara göre doldur:
*/

// int main()
// {
//     // 1) Kamerayı aç

//     // 2) Açılmadıysa çık

//     // 3) Sonsuz döngü

//     // Zaman ölçümü için t1 al

//     // Frame oku, boşsa break

//     // Gerekirse basit bir işlem (opsiyonel)

//     // t2 al, deltaTime ve fps hesapla

//     // FPS string'i oluştur

//     // FPS'yi frame üzerine yaz (putText)

//     // Frame'i göster

//     // 'q' gelirse break

//     // Kaynakları temizle

//     return 0;
// }

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // 1) Kamerayı aç
    cv::VideoCapture cap(0);

    // 2) Kamera açılmadıysa çık
    if (!cap.isOpened())
    {
        std::cout << "Kamera acilmadi..." << std::endl;
        return -1;
    }

    while (true)
    {
        // Döngü başında zaman sayacını al
        int64 t1 = cv::getTickCount();

        cv::Mat frame;

        // Frame oku
        cap.read(frame);
        if (frame.empty())
        {
            std::cout << "Frame okunamadi, cikiliyor..." << std::endl;
            break;
        }

        // (Opsiyonel) Burada frame'e filtre/işlem uygulayabilirsin
        // Örnek: griye çevir vs. Ama FPS ölçümü mantığı değişmez.

        // Döngü sonunda zaman sayacını al
        int64 t2 = cv::getTickCount();

        // deltaTime: 1 frame'in işlenme süresi (saniye cinsinden)
        double deltaTime = (t2 - t1) / cv::getTickFrequency();

        // FPS = 1 / süre
        double fps = 0.0;
        if (deltaTime > 0.0)
            fps = 1.0 / deltaTime;

        // FPS string'ini hazırla (virgülden sonra biraz kırpabiliriz)
        std::string fpsText = "FPS: " + std::to_string(static_cast<int>(fps));

        // FPS'yi frame üzerine yaz
        cv::putText(
            frame,
            fpsText,
            cv::Point(10, 30), // sol üst köşe
            cv::FONT_HERSHEY_SIMPLEX,
            0.8,
            cv::Scalar(0, 255, 0), // yeşil
            2);

        // Frame'i göster
        cv::imshow("Kamera + FPS", frame);

        // 'q' gelirse çık
        char c = static_cast<char>(cv::waitKey(1));
        if (c == 'q' || c == 'Q')
        {
            break;
        }
    }

    // Kaynakları temizle
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
