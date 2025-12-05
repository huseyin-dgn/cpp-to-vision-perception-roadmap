/*
🧩 SORU 4 — CANLI AKIŞTA KIRMIZI MASKE GÖSTER

Görevlerin:

1) Kamerayı aç:
      cv::VideoCapture cap(0);

2) Kamera açılmadıysa programı bitir.

3) Sonsuz döngü başlat:
      while (true) { ... }

4) Döngü içinde:
      - Kameradan frame oku
      - Frame boşsa break;

5) Frame'i BGR'den HSV'ye çevir:
      cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
   Yorum satırı:
      HSV, renge göre maskelemede BGR'ye göre daha stabildir.

6) Kırmızı renk için iki HSV aralığı tanımla:
      lower_red1(0, 120, 70),   upper_red1(10, 255, 255)
      lower_red2(170, 120, 70), upper_red2(180, 255, 255)

   Bu aralıklar için:
      cv::inRange(hsv, lower_red1, upper_red1, mask1);
      cv::inRange(hsv, lower_red2, upper_red2, mask2);

7) İki maskeyi birleştir:
      cv::bitwise_or(mask1, mask2, mask);

8) Orijinal görüntüyü ve mask'i göster:
      "Orijinal" → frame
      "Kirmizi Maske" → mask

9) 'q' veya 'Q' basılırsa döngüden çık.

10) cap.release() + destroyAllWindows() ile bitir.

Aşağıdaki iskeleti doldur:
*/

// #include <iostream>
// #include <opencv2/opencv.hpp>

// int main()
// {
//     // 1) Kamerayı aç

//     // 2) Açılmadıysa çık

//     // 3) Sonsuz döngü

//     // frame, hsv, mask1, mask2, mask tanımla

//     // 4) Frame oku

//     // Frame boşsa break

//     // 5) BGR -> HSV çevir

//     // 6) Kırmızı için iki aralık inRange ile maskele

//     // 7) Maskeleri bitwise_or ile birleştir

//     // 8) Orijinal ve mask'i göster

//     // 9) 'q' gelirse çık

//     // 10) Kaynak temizliği

//     return 0;
// }

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // 1) Kamerayı aç
    cv::VideoCapture cap(0);

    // 2) Açılmadıysa çık
    if (!cap.isOpened())
    {
        std::cout << "Kamera acilmadi..." << std::endl;
        return -1;
    }

    while (true)
    {
        cv::Mat frame;
        cv::Mat hsv;
        cv::Mat mask1, mask2, mask;

        // 4) Frame oku
        cap.read(frame);
        if (frame.empty())
        {
            std::cout << "Frame okunamadi, cikiliyor..." << std::endl;
            break;
        }

        // 5) BGR -> HSV
        // HSV (Hue, Saturation, Value) renk uzayı:
        // Renge göre maskelemede BGR'ye göre daha stabildir.
        cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

        // 6) Kırmızı için iki HSV aralığı
        // Not: Kırmızı, HSV'de 0'a ve 180'e yakın 2 bölgede dağılır.
        cv::Scalar lower_red1(0, 120, 70);
        cv::Scalar upper_red1(10, 255, 255);
        cv::Scalar lower_red2(170, 120, 70);
        cv::Scalar upper_red2(180, 255, 255);

        cv::inRange(hsv, lower_red1, upper_red1, mask1);
        cv::inRange(hsv, lower_red2, upper_red2, mask2);

        // 7) Maskeleri birleştir
        cv::bitwise_or(mask1, mask2, mask);

        // 8) Orijinal görüntü ve maske göster
        cv::imshow("Orijinal", frame);
        cv::imshow("Kirmizi Maske", mask);

        // 9) 'q' gelirse çık
        char c = static_cast<char>(cv::waitKey(1));
        if (c == 'q' || c == 'Q')
        {
            break;
        }
    }

    // 10) Kaynak temizliği
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
