/*
🧩 SORU 3 — CANLI AKIŞTA CANNY KENARLARI

Görevlerin:

1) Kamerayı aç:
      cv::VideoCapture cap(0);

2) Kamera açılmazsa programı bitir.

3) Sonsuz döngüde:
      - Frame oku
      - Frame boşsa break

4) Frame'i griye çevir:
      cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

5) Gri görüntüye hafif blur uygula:
      cv::GaussianBlur(gray, blur, Size(5,5), 0);
   Not: Canny gürültüye hassas, blur ile yumuşatıyoruz.

6) Canny kenar tespiti uygula:
      cv::Canny(blur, edges, 100, 200);
   Not (yorum satırı olarak yaz):
      - lower threshold: 100
      - upper threshold: 200

7) Aşağıdaki pencereleri göster:
      - "Orijinal" → frame
      - "Gri"      → gray
      - "Canny"    → edges

8) waitKey(1) ile 'q' basılınca çık.

9) En sonda cap.release() + destroyAllWindows().

Aşağıdaki main fonksiyonunu doldur:
*/

// int main()
// {
//     // 1) Kamerayı aç

//     // 2) Açılmadıysa çık

//     // 3) Sonsuz döngü

//         // Frame, gray, blur, edges tanımla

//         // Frame oku

//         // Frame boşsa break

//         // 4) Griye çevir

//         // 5) Blur uygula

//         // 6) Canny uygula

//         // 7) Orijinal, Gri, Canny göster

//         // 8) 'q' gelirse çık

//     // 9) Kaynakları temizle

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
        cv::Mat gray;
        cv::Mat blur;
        cv::Mat edges;

        // Frame oku
        cap.read(frame);
        if (frame.empty())
        {
            std::cout << "Frame okunamadi, cikiliyor..." << std::endl;
            break;
        }

        // 4) Griye çevir
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // 5) Gaussian blur uygula
        // Canny öncesi gürültüyü azaltmak için:
        cv::GaussianBlur(gray, blur, cv::Size(5, 5), 0);

        // 6) Canny kenar tespiti
        // 100 -> lower threshold
        // 200 -> upper threshold
        cv::Canny(blur, edges, 100, 200);

        // 7) Pencereleri göster
        cv::imshow("Orijinal", frame);
        cv::imshow("Gri", gray);
        cv::imshow("Canny", edges);

        // 8) 'q' gelirse çık
        char c = static_cast<char>(cv::waitKey(1));
        if (c == 'q' || c == 'Q')
        {
            break;
        }
    }

    // 9) Kaynakları temizle
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
