/*
🧩 SORU 2 — CANLI AKIŞTA HEM ORİJİNAL HEM GRİ GÖSTER

Görevlerin:

1) Varsayılan kamerayı aç:
      cv::VideoCapture cap(0);

2) Kamera açılmadıysa programdan çık:
      if (!cap.isOpened()) { ... }

3) Sonsuz döngü başlat:
      while (true) { ... }

4) Döngü içinde:
      a) Kameradan bir frame oku: cap.read(frame);
      b) Frame bos geldiyse break;

5) Okunan frame'den gri görüntü üret:
      cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

6) İki ayrı pencere göster:
      "Orijinal" → renkli frame
      "Gri"      → gray

7) Her iterasyonda:
      - cv::waitKey(1) ile klavyeden tuş oku
      - Eğer 'q' veya 'Q' basılırsa döngüden çık

8) Program biterken:
      - cap.release();
      - cv::destroyAllWindows();

Aşağıdaki main fonksiyonunu bu adımlara göre doldur:
*/

// #include <iostream>
// #include <opencv2/opencv.hpp>

// int main()
// {
//     // 1) Kamerayı aç

//     // 2) Açılmadıysa çık

//     // 3) Sonsuz döngü

//     // 4) Frame oku

//     // 5) Griye çevir

//     // 6) Orijinal ve griyi göster

//     // 7) 'q' gelirse çık

//     // 8) Kaynakları temizle

//     return 0;
// }

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // 1) Kamerayı aç (0 = varsayılan webcam)
    cv::VideoCapture cap(0);

    // 2) Kamera açıldı mı kontrol et
    if (!cap.isOpened())
    {
        std::cout << "Kamera acilmadi..." << std::endl;
        return -1;
    }

    while (true)
    {
        cv::Mat frame;
        cv::Mat gray;

        // 4) Kameradan frame oku
        cap.read(frame); // cap >> frame; de yazılabilir

        // Frame bos gelirse kamera kopmuş demektir
        if (frame.empty())
        {
            std::cout << "Frame okunamadi, cikiliyor..." << std::endl;
            break;
        }

        // 5) Renkli (BGR) görüntüyü gri tona çevir
        // BGR -> GRAY (1 kanallı)
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // 6) Orijinal ve gri görüntüyü göster
        cv::imshow("Orijinal", frame);
        cv::imshow("Gri", gray);

        // 7) Her frame'de 1 ms bekle, 'q' gelirse çık
        char c = static_cast<char>(cv::waitKey(1));
        if (c == 'q' || c == 'Q')
        {
            break;
        }
    }

    // 8) Kaynakları temizle
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
