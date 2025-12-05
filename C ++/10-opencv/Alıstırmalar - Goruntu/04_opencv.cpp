/*
🧩 SORU 5 – Sobel, Scharr ve Laplacian filtreleriyle kenar tespiti

Görevlerin:

1) "image.jpg" dosyasını oku.

2) Görüntüyü griye çevir.
   (Sobel, Scharr ve Laplacian tek kanal ister.)

3) Sobel filtresi uygula:
   - SobelX: X yönünde kenarlar (yatay kenarlar)
     cv::Sobel(gray, sobelX, CV_64F, 1, 0, 3)
   - SobelY: Y yönünde kenarlar (dikey kenarlar)
     cv::Sobel(gray, sobelY, CV_64F, 0, 1, 3)

   Yorum satırlarında:
   - Sobel’in birinci türev aldığını
   - 3×3 kernel kullandığını
   - X türevinde yatay değişimleri bulduğunu
   - Y türevinde dikey değişimleri bulduğunu anlat.

4) Mutlak değer alıp 8-bit’e dönüştür:
     convertScaleAbs(...)

5) X ve Y sonuçlarını birleştir:
     cv::addWeighted(sobelX_8, 0.5, sobelY_8, 0.5, 0, sobelCombined);

6) Laplacian uygula:
     cv::Laplacian(gray, lap, CV_64F)
   - Laplacian’ın ikinci türev olduğunu yorumla.
   - Tek kernel → hem yatay hem dikey kenarları birlikte bulur.

7) Hepsini göster:
   - Orijinal
   - Gri
   - Sobel X
   - Sobel Y
   - Sobel Combined
   - Laplacian

8) Sonuçları kaydet:
   - sobel_x.jpg
   - sobel_y.jpg
   - sobel_combined.jpg
   - laplacian.jpg

Aşağıdaki iskelet kodu tamamla:

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // Oku

    // Gri

    // Sobel X

    // Sobel Y

    // X ve Y birleştir

    // Laplacian

    // Göster

    // Kaydet

    return 0;
}
*/

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
   // 1) Görüntüyü oku
   cv::Mat img = cv::imread("test.jpg", cv::IMREAD_COLOR);
   if (img.empty())
   {
      std::cout << "Goruntu yuklenemedi!" << std::endl;
      return -1;
   }

   // 2) Griye çevir
   cv::Mat gray;
   cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

   // --- SOBEL ---
   // Sobel birinci türev alır. 3x3 kernel ile gradyan hesaplar.

   cv::Mat sobelX, sobelY;

   // dX = 1 → x yönünde türev (yatay kenarlar)
   cv::Sobel(gray, sobelX, CV_64F, 1, 0, 3);

   // dY = 1 → y yönünde türev (dikey kenarlar)
   cv::Sobel(gray, sobelY, CV_64F, 0, 1, 3);

   // Mutlak değer ve 8-bit’e çevir
   cv::Mat sobelX_8, sobelY_8;
   cv::convertScaleAbs(sobelX, sobelX_8);
   cv::convertScaleAbs(sobelY, sobelY_8);

   // X ve Y birleşimi
   cv::Mat sobelCombined;
   cv::addWeighted(sobelX_8, 0.5, sobelY_8, 0.5, 0, sobelCombined);

   // --- LAPLACIAN ---
   // Laplacian ikinci türevdir.
   // Hem yatay hem dikey gradyanı aynı kernel ile bulur.
   cv::Mat lap, lap_8;
   cv::Laplacian(gray, lap, CV_64F);
   cv::convertScaleAbs(lap, lap_8);

   // --- GÖSTER ---
   cv::imshow("Orijinal", img);
   cv::imshow("Gri", gray);
   cv::imshow("Sobel X", sobelX_8);
   cv::imshow("Sobel Y", sobelY_8);
   cv::imshow("Sobel Combined", sobelCombined);
   cv::imshow("Laplacian", lap_8);

   // --- KAYDET ---
   cv::imwrite("sobel_x.jpg", sobelX_8);
   cv::imwrite("sobel_y.jpg", sobelY_8);
   cv::imwrite("sobel_combined.jpg", sobelCombined);
   cv::imwrite("laplacian.jpg", lap_8);

   cv::waitKey(0);
   cv::destroyAllWindows();

   return 0;
}
