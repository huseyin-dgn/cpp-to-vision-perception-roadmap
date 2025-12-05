/*
🧩 SORU 6 – Morfolojik İşlemler (Erosion, Dilation, Opening, Closing)

Görevlerin:

1) "image.jpg" dosyasını oku ve gri tona çevir.
   - Bu işlemler genellikle binary görüntülerde yapılır, ama gri görüntü ile başlatacağız.

2) Binary görüntü oluşturmak için threshold uygula:
   cv::threshold(gray, binary, 128, 255, cv::THRESH_BINARY);

3) 3×3 kernel tanımla:
   cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

4) Aşağıdaki işlemleri uygula:

   ▪ Erosion (Aşındırma)
     cv::erode(binary, eroded, kernel);
     Açıklama: Beyaz bölgeleri küçültür, gürültüyü azaltır.

   ▪ Dilation (Genleşme)
     cv::dilate(binary, dilated, kernel);
     Açıklama: Beyaz bölgeleri büyütür; kopuk bölgeleri birleştirebilir.

   ▪ Opening = Erosion → Dilation
     cv::morphologyEx(binary, opening, cv::MORPH_OPEN, kernel);
     Açıklama: Gürültü temizleme için idealdir.

   ▪ Closing = Dilation → Erosion
     cv::morphologyEx(binary, closing, cv::MORPH_CLOSE, kernel);
     Açıklama: Delikleri kapatma ve nesneyi toparlama için idealdir.

5) Aşağıdaki pencereleri göster:
   - Orijinal
   - Binary
   - Eroded
   - Dilated
   - Opening
   - Closing

6) Sonuçları kaydet:
   - eroded.jpg
   - dilated.jpg
   - opening.jpg
   - closing.jpg

Aşağıdaki iskelet kodu tamamla:

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // Oku

    // Gri

    // Threshold

    // Kernel

    // Erosion

    // Dilation

    // Opening

    // Closing

    // Göster

    return 0;
}
*/

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // 1) Oku
    cv::Mat img = cv::imread("test.jpg", cv::IMREAD_COLOR);
    if (img.empty())
    {
        std::cout << "Goruntu yuklenemedi!" << std::endl;
        return -1;
    }

    // 2) Gri görüntü
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    // 3) Binary görüntü
    cv::Mat binary;
    cv::threshold(gray, binary, 128, 255, cv::THRESH_BINARY);

    // 4) 3x3 kernel
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

    // --- Erosion ---
    cv::Mat eroded;
    // Beyaz bölgeleri küçültür, küçük gürültüleri yok eder.
    cv::erode(binary, eroded, kernel);

    // --- Dilation ---
    cv::Mat dilated;
    // Beyaz bölgeleri büyütür, kopuk yerleri birleştirebilir.
    cv::dilate(binary, dilated, kernel);

    // --- Opening (Erosion -> Dilation) ---
    cv::Mat opening;
    // Gürültüyü temizler, ince siyah noktaları yok eder.
    cv::morphologyEx(binary, opening, cv::MORPH_OPEN, kernel);

    // --- Closing (Dilation -> Erosion) ---
    cv::Mat closing;
    // Beyaz nesnelerdeki boşlukları kapatır.
    cv::morphologyEx(binary, closing, cv::MORPH_CLOSE, kernel);

    // --- GÖSTER ---
    cv::imshow("Orijinal", img);
    cv::imshow("Binary", binary);
    cv::imshow("Eroded", eroded);
    cv::imshow("Dilated", dilated);
    cv::imshow("Opening", opening);
    cv::imshow("Closing", closing);

    // --- KAYDET ---
    cv::imwrite("eroded.jpg", eroded);
    cv::imwrite("dilated.jpg", dilated);
    cv::imwrite("opening.jpg", opening);
    cv::imwrite("closing.jpg", closing);

    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}
