/*
🧩 SORU 10 — CANLI HSV TRACKBAR İLE RENK MASKELEME

Amaç:
- Kameradan gelen görüntüyü HSV'ye çevir.
- 6 tane trackbar ile alt/üst H, S, V değerlerini canlı ayarla:
    H_low, H_high, S_low, S_high, V_low, V_high
- Bu değerlere göre inRange ile maske üret.
- Orijinal + Maske'yi ekranda göster.

Görevlerin:

1) Kamerayı aç:
      cv::VideoCapture cap(0);
   Açılmazsa exit.

2) "Kontroller" adında boş bir pencere oluştur:
      cv::namedWindow("Kontroller");

3) Aşağıdaki 6 trackbar'ı bu pencere üzerinde oluştur:
      int h_low = 0,   h_high = 179;
      int s_low = 0,   s_high = 255;
      int v_low = 0,   v_high = 255;

      cv::createTrackbar("H Low",  "Kontroller", &h_low,  179);
      cv::createTrackbar("H High", "Kontroller", &h_high, 179);
      cv::createTrackbar("S Low",  "Kontroller", &s_low,  255);
      cv::createTrackbar("S High", "Kontroller", &s_high, 255);
      cv::createTrackbar("V Low",  "Kontroller", &v_low,  255);
      cv::createTrackbar("V High", "Kontroller", &v_high, 255);

4) Sonsuz döngü:
      - Kameradan frame oku, boşsa break
      - BGR -> HSV çevir

      - Trackbar değerlerini oku (direkt h_low, h_high vs değişkenleri kullan)
      - lower = Scalar(h_low, s_low, v_low)
      - upper = Scalar(h_high, s_high, v_high)

      - inRange(hsv, lower, upper, mask) ile maske üret

      - Orijinal görüntüyü "Orijinal" penceresinde göster
      - mask'i "Maske" penceresinde göster

      - 'q' gelirse çık

5) cap.release() + destroyAllWindows() ile bitir.

Not:
- H için max değer: 179
- S, V için max değer: 255

Aşağıdaki main fonksiyonunu bu adımlara göre doldur:
*/

// int main()
// {
//     // 1) Kamerayı aç

//     // 2) Kontrol penceresi ve trackbar'lar

//     // 3) Sonsuz döngü

//     // Frame, hsv, mask tanımla

//     // Frame oku, boşsa break

//     // BGR -> HSV

//     // Trackbar değerlerine göre lower/upper Scalar oluştur

//     // inRange ile maske üret

//     // Orijinal ve maske'yi göster

//     // 'q' gelirse break

//     // 4) Kaynakları temizle

//     return 0;
// }

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // 1) Kamerayı aç
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        std::cout << "Kamera acilmadi..." << std::endl;
        return -1;
    }

    // 2) Kontrol penceresi ve trackbar değişkenleri
    cv::namedWindow("Kontroller");

    int h_low = 0;
    int h_high = 179; // Hue 0-179 arasi
    int s_low = 0;
    int s_high = 255;
    int v_low = 0;
    int v_high = 255;

    cv::createTrackbar("H Low", "Kontroller", &h_low, 179);
    cv::createTrackbar("H High", "Kontroller", &h_high, 179);
    cv::createTrackbar("S Low", "Kontroller", &s_low, 255);
    cv::createTrackbar("S High", "Kontroller", &s_high, 255);
    cv::createTrackbar("V Low", "Kontroller", &v_low, 255);
    cv::createTrackbar("V High", "Kontroller", &v_high, 255);

    while (true)
    {
        cv::Mat frame;
        cv::Mat hsv;
        cv::Mat mask;

        // Frame oku
        cap.read(frame);
        if (frame.empty())
        {
            std::cout << "Frame okunamadi, cikiliyor..." << std::endl;
            break;
        }

        // BGR -> HSV
        cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

        // Trackbar değerlerine göre alt/üst sınır oluştur
        cv::Scalar lower(h_low, s_low, v_low);
        cv::Scalar upper(h_high, s_high, v_high);

        // Maskeyi üret
        cv::inRange(hsv, lower, upper, mask);

        // Görüntüleri göster
        cv::imshow("Orijinal", frame);
        cv::imshow("Maske", mask);

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
