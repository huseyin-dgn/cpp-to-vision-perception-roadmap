/*
🧩 SORU 5 — CANLI AKIŞTA KIRMIZI NESNEYİ BUL VE KUTU ÇİZ

Görevlerin:

1) Kamerayı aç:
      cv::VideoCapture cap(0);

2) Kamera açılmazsa programdan çık.

3) Sonsuz döngü başlat:
      while (true) { ... }

4) Döngü içinde:
      - Frame oku (cap.read(frame))
      - Frame boşsa break;

5) Frame'i HSV'ye çevir:
      cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

6) Kırmızı rengin iki HSV aralığı için maske oluştur:
      inRange(hsv, lower_red1, upper_red1, mask1);
      inRange(hsv, lower_red2, upper_red2, mask2);

7) Maskeleri birleştir:
      bitwise_or(mask1, mask2, mask);

8) Maskeyi biraz temizlemek için:
      - GaussianBlur veya
      - morphologyEx (MORPH_OPEN) kullanabilirsin.
      (En az bir tane uygula, noise azalsın.)

9) Temiz maskeden konturları bul:
      findContours(maskClean, contours, hierarchy,
                   RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

10) Eğer kontur varsa:
      - En büyük alanlı konturu bul (contourArea ile)
      - Bu kontur için boundingRect hesapla
      - Orijinal frame üstüne rectangle ile yeşil kutu çiz

11) Aşağıdakileri göster:
      - "Orijinal"  → kutu çizilmiş frame
      - "Kirmizi Maske" → maskClean

12) waitKey(1) ile 'q' veya 'Q' gelirse döngüden çık.

13) Döngü bitince:
      cap.release();
      destroyAllWindows();

Aşağıdaki main fonksiyonunu bu adımlara göre doldur:
*/

// #include <iostream>
// #include <opencv2/opencv.hpp>

// int main()
// {
//     // 1) Kamerayı aç

//     // 2) Açılmadıysa çık

//     // 3) Sonsuz döngü

//     // frame, hsv, mask1, mask2, mask, maskClean tanımla

//     // 4) Frame oku

//     // Frame boşsa break

//     // 5) BGR -> HSV çevir

//     // 6) Kırmızı için iki maske (inRange)

//     // 7) Maskeleri birleştir (bitwise_or)

//     // 8) Maskeyi temizle (GaussianBlur veya morphologyEx)

//     // 9) Contour bul (findContours)

//     // 10) En büyük konturu bul, boundingRect al, frame üstüne rectangle çiz

//     // 11) Orijinal + Maske göster

//     // 12) 'q' gelirse break

//     // 13) Kaynakları temizle

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
        cv::Mat frame;
        cv::Mat hsv;
        cv::Mat mask1, mask2, mask, maskClean;

        // 4) Frame oku
        cap.read(frame);
        if (frame.empty())
        {
            std::cout << "Frame okunamadi, cikiliyor..." << std::endl;
            break;
        }

        // 5) BGR -> HSV
        cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
        // HSV: Hue (renk), Saturation (doygunluk), Value (parlaklik)
        // Renge göre maskelemede BGR'ye göre daha stabildir.

        // 6) Kırmızı için iki HSV aralığı
        cv::Scalar lower_red1(0, 120, 70);
        cv::Scalar upper_red1(10, 255, 255);
        cv::Scalar lower_red2(170, 120, 70);
        cv::Scalar upper_red2(180, 255, 255);

        cv::inRange(hsv, lower_red1, upper_red1, mask1);
        cv::inRange(hsv, lower_red2, upper_red2, mask2);

        // 7) Maskeleri birleştir
        cv::bitwise_or(mask1, mask2, mask);

        // 8) Maskeyi biraz temizle (gürültüyü azalt)
        // Gaussian blur:
        cv::GaussianBlur(mask, maskClean, cv::Size(5, 5), 0);

        // İstersen ek olarak açma işlemi de yapabilirsin:
        // cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
        // cv::morphologyEx(maskClean, maskClean, cv::MORPH_OPEN, kernel);

        // 9) Contour bul
        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;

        cv::findContours(maskClean, contours, hierarchy,
                         cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        // 10) En büyük konturu bul ve bounding box çiz
        if (!contours.empty())
        {
            double maxArea = 0.0;
            int maxIdx = -1;

            for (size_t i = 0; i < contours.size(); ++i)
            {
                double area = cv::contourArea(contours[i]);
                if (area > maxArea)
                {
                    maxArea = area;
                    maxIdx = static_cast<int>(i);
                }
            }

            if (maxIdx != -1 && maxArea > 200.0) // çok küçük gürültüyü at
            {
                cv::Rect bbox = cv::boundingRect(contours[maxIdx]);

                // Orijinal frame üzerina yeşil kutu çiz
                cv::rectangle(frame, bbox, cv::Scalar(0, 255, 0), 2);

                // İstersen ortasına küçük bir nokta da koyabilirsin:
                // cv::Point center(bbox.x + bbox.width/2, bbox.y + bbox.height/2);
                // cv::circle(frame, center, 3, cv::Scalar(255, 0, 0), -1);
            }
        }

        // 11) Göster
        cv::imshow("Orijinal + Bounding Box", frame);
        cv::imshow("Kirmizi Maske", maskClean);

        // 12) 'q' gelirse çık
        char c = static_cast<char>(cv::waitKey(1));
        if (c == 'q' || c == 'Q')
        {
            break;
        }
    }

    // 13) Kaynakları temizle
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
