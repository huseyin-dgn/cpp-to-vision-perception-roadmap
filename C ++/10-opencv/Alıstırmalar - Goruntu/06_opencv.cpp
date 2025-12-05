/*
🧩 SORU 7 – Görüntüdeki konturları bul ve çiz

Görevlerin:

1) "image.jpg" dosyasını oku.

2) Griye çevir.

3) Blur uygula (GaussianBlur 5x5).
   Açıklama: Gürültüyü azaltıp temiz kontur bulmak için.

4) Threshold uygula:
   cv::threshold(gray, binary, 100, 255, cv::THRESH_BINARY);

5) Konturları bul:
   std::vector<std::vector<cv::Point>> contours;
   cv::findContours(binary, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

   Açıklamalar (yorum satırı olarak yaz):
   ▪ RETR_EXTERNAL → sadece dış konturları alır
   ▪ CHAIN_APPROX_SIMPLE → gereksiz piksel noktalarını atar, konturu sıkıştırır

6) Yeni bir boş görüntü oluştur:
   cv::Mat output = img.clone();

7) Konturları çiz:
   cv::drawContours(output, contours, -1, cv::Scalar(0, 0, 255), 2);

   Açıklama:
   - -1 → tüm konturları çiz
   - Scalar(0,0,255) → kırmızı
   - kalınlık = 2

8) Pencereleri göster:
   Orijinal, Binary, Kontur

9) "contours.jpg" dosyasına kaydet.

İskelet kodu tamamla:

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // 1) Oku

    // 2) Gri

    // 3) Blur

    // 4) Threshold

    // 5) findContours

    // 6) output clone

    // 7) drawContours

    // 8) göster

    // 9) kaydet

    return 0;
}
*/

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // 1) Oku
    cv::Mat img = cv::imread("image.jpg");
    if (img.empty())
    {
        std::cout << "Goruntu yuklenemedi!" << std::endl;
        return -1;
    }

    // 2) Gri
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    // 3) Blur
    cv::Mat blurImg;
    cv::GaussianBlur(gray, blurImg, cv::Size(5, 5), 0);

    // 4) Threshold (binary görüntü)
    cv::Mat binary;
    cv::threshold(blurImg, binary, 100, 255, cv::THRESH_BINARY);

    // 5) Kontur bul
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    // RETR_EXTERNAL → sadece dış konturlar
    // CHAIN_APPROX_SIMPLE → gereksiz noktaları atıp konturu sadeleştirir
    cv::findContours(binary, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 6) Çizim için kopya
    cv::Mat output = img.clone();

    // 7) Konturları çiz
    // -1 → tüm konturları çiz
    // Scalar(0,0,255) → kırmızı çiz
    cv::drawContours(output, contours, -1, cv::Scalar(0, 0, 255), 2);

    // 8) Göster
    cv::imshow("Orijinal", img);
    cv::imshow("Binary", binary);
    cv::imshow("Kontur", output);

    // 9) Kaydet
    cv::imwrite("contours.jpg", output);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
