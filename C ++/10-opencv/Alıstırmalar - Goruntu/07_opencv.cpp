/*
🧩 SORU 8 – Konturlara dikdörtgen çiz (Bounding Box)

Görevlerin:

1) "image.jpg" dosyasını oku.

2) Griye çevir, blur uygula, threshold ile binary görüntü oluştur:
   - cvtColor → COLOR_BGR2GRAY
   - GaussianBlur(gray, blurImg, Size(5,5), 0)
   - threshold(blurImg, binary, 100, 255, THRESH_BINARY)

3) Konturları bul:
   std::vector<std::vector<cv::Point>> contours;
   findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

4) Her kontur için:
   - Alanı hesapla: double area = contourArea(contours[i]);
   - Eğer area küçükse (örneğin < 100) → continue (gürültüyü geç)

   - Axis-aligned bounding box:
       cv::Rect bbox = boundingRect(contours[i]);

5) Orijinal görüntü üzerinde dikdörtgen çiz:
   - cv::rectangle(output, bbox, Scalar(0,255,0), 2);

6) Kontur sayısını ekrana yaz:
   std::cout << "Bulunan kontur sayisi: " << contours.size() << std::endl;

7) "bbox.jpg" adıyla kaydet.

İskeleti tamamla:

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // 1) Oku

    // 2) Gri + Blur + Threshold

    // 3) Kontur bul

    // 4) BoundingRect hesapla

    // 5) Dikdörtgen çiz

    // 6) Göster + Kaydet

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

    // 2) Gri + Blur + Threshold
    cv::Mat gray, blurImg, binary;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray, blurImg, cv::Size(5, 5), 0);
    cv::threshold(blurImg, binary, 100, 255, cv::THRESH_BINARY);

    // 3) Kontur bul
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(binary, contours, hierarchy,
                     cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    std::cout << "Bulunan kontur sayisi: " << contours.size() << std::endl;

    // Çizim için kopya
    cv::Mat output = img.clone();

    // 4) Her kontur için bounding box
    for (size_t i = 0; i < contours.size(); ++i)
    {
        double area = cv::contourArea(contours[i]);
        if (area < 100.0)
            continue; // çok küçük gürültüleri atla

        cv::Rect bbox = cv::boundingRect(contours[i]);

        // 5) Dikdörtgen çiz (yeşil, kalınlık 2)
        cv::rectangle(output, bbox, cv::Scalar(0, 255, 0), 2);
    }

    // 6) Göster + Kaydet
    cv::imshow("Orijinal", img);
    cv::imshow("Binary", binary);
    cv::imshow("Bounding Box", output);

    cv::imwrite("bbox.jpg", output);

    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}
