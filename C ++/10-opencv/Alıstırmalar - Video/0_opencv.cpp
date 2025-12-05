/*
🧩 SORU 1 — CANLI KAMERA AÇMA VE FRAME GÖSTERME

Görevlerin:

1) Bilgisayardaki varsayılan kamerayı aç:
      cv::VideoCapture cap(0);
   Açıklama: 0 → varsayılan kamera ID.

2) Kamera açılmadıysa programı bitir:
      cap.isOpened()
   Açıklama: Kamera başka program tarafından kullanılıyorsa false döner.

3) Sonsuz döngü başlat:
      while (true) { ... }

4) Döngü içinde kameradan bir frame oku:
      cap.read(frame);
   Açıklama: frame boş gelirse kamera bağlantısı kopmuştur.

5) Okunan frame’i ekranda göster:
      cv::imshow("Kamera", frame);

6) Kullanıcı bir tuşa bastığında çık:
      if (cv::waitKey(1) == 'q') break;

7) Program biterken kamerayı serbest bırak:
      cap.release();
      cv::destroyAllWindows();

Aşağıdaki iskelet fonksiyonu TAMAMLA:
*/

// int main()
// {
//     // 1) Kamerayı aç

//     // 2) Açılmadıysa çık

//     // 3) Sonsuz döngü

//         // 4) Frame oku

//         // 5) Göster

//         // 6) Çıkış koşulu

//     // 7) Kaynakları serbest bırak

//     return 0;
// }

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    cv::VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cout << "Kamera acılmadı...";
        return -1;
    }

    while (true)
    {
        cv::Mat frame;

        cap.read(frame);

        if (frame.empty())
        {
            std::cout << "Frame okunamadı...";
            break;
        }

        cv::imshow("Kamera", frame);
        char c = static_cast<char>(cv::waitKey(1));

        if (c == 'q' || c == 'Q')
        {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
