/*
🧩 Renge Göre Nesne Tespiti – Kırmızı Bölgeyi Bul ve Kutula

Görevlerin:

1) "image.jpg" dosyasını oku (BGR renkli).

2) Görüntüyü HSV renk uzayına çevir:
   - cvtColor(img, hsv, COLOR_BGR2HSV)
   - Yorum satırında HSV'nin avantajını kısaca yaz.

3) Kırmızı renk için bir maske oluştur:
   - cv::inRange ile alt ve üst HSV sınırlarını kullan.
   - Örn: lower_red1, upper_red1, lower_red2, upper_red2 gibi iki aralık (HSV'de kırmızı wrap-around yaptığı için).

4) İki maskeyi birleştir (bitwise_or).

5) Maskeyi biraz temizlemek için:
   - GaussianBlur veya morphology (erode/dilate) uygulayabilirsin (en az 1 tane uygula).

6) Maskeden kontur bul:
   - findContours(mask, contours, ...)

7) En büyük alana sahip konturu bul:
   - contourArea ile max alanı hesapla.
   - Ona karşılık gelen boundingRect'i al.

8) Orijinal görüntü üzerinde bu bounding box'ı çiz:
   - rectangle(output, bbox, Scalar(0,255,0), 2)

9) Sonuçları göster:
   - Orijinal
   - Maske
   - Sonuç (bbox çizili görüntü)

10) Son görüntüyü "red_detect.jpg" olarak kaydet.

İskelet:

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // 1) Oku

    // 2) BGR -> HSV

    // 3) Kırmızı maske

    // 4) Maskeleri birleştir

    // 5) Temizleme (blur veya morphology)

    // 6) Kontur bul

    // 7) En büyük konturu seç

    // 8) Bounding box çiz

    // 9) Göster + Kaydet

    return 0;
}
*/

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // 1) Görüntüyü oku
    cv::Mat img = cv::imread("test.jpg");
    if (img.empty())
    {
        std::cout << "Goruntu yuklenemedi!" << std::endl;
        return -1;
    }

    // 2) BGR -> HSV
    cv::Mat hsv;
    // HSV: Hue (renk), Saturation (doygunluk), Value (parlaklık)
    // Renge göre maskelemede BGR'den çok daha stabildir.
    cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);

    // 3) Kırmızı renk aralıkları
    // Not: HSV'de kırmızı, 0'a yakın ve 180'e yakın bölgede iki parçaya dağılır.
    cv::Mat mask1, mask2, mask;

    // Alt kırmızı aralık (örn: 0-10)
    cv::Scalar lower_red1(0, 120, 70);
    cv::Scalar upper_red1(10, 255, 255);
    cv::inRange(hsv, lower_red1, upper_red1, mask1);

    // Üst kırmızı aralık (örn: 170-180)
    cv::Scalar lower_red2(170, 120, 70);
    cv::Scalar upper_red2(180, 255, 255);
    cv::inRange(hsv, lower_red2, upper_red2, mask2);

    // 4) Maskeleri birleştir
    cv::bitwise_or(mask1, mask2, mask);

    // 5) Maskeyi biraz temizle (opsiyonel ama faydalı)
    cv::Mat maskClean;
    cv::GaussianBlur(mask, maskClean, cv::Size(5, 5), 0);
    // İstersen morphology de ekleyebilirsin:
    // cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));
    // cv::morphologyEx(maskClean, maskClean, cv::MORPH_OPEN, kernel);

    // 6) Kontur bul
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(maskClean, contours, hierarchy,
                     cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    cv::Mat output = img.clone();

    if (!contours.empty())
    {
        // 7) En büyük konturu seç
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

        if (maxIdx != -1 && maxArea > 100.0) // çok küçük değilse
        {
            cv::Rect bbox = cv::boundingRect(contours[maxIdx]);

            // 8) Bounding box çiz (yeşil)
            cv::rectangle(output, bbox, cv::Scalar(0, 255, 0), 2);
        }
    }

    // 9) Göster + Kaydet
    cv::imshow("Orijinal", img);
    cv::imshow("Kirmizi Maske", maskClean);
    cv::imshow("Sonuc", output);

    cv::imwrite("red_detect.jpg", output);

    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}
