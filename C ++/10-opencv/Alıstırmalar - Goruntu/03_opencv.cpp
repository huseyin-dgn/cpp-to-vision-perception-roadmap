/*
🧩 SORU 4 – Canny Edge Detection ile kenar bulma

Görevlerin:

1) Çalışma klasöründeki "image.jpg" dosyasını oku.

2) Okunan görüntüyü gri tona çevir.
   - COLOR_BGR2GRAY kullan.
   - Neden gri çevirdiğini açıklayan bir yorum satırı yaz.
     (İpucu: Kenar bulma algoritmaları tek kanal üzerinde çalışır.)

3) Gaussian Blur uygula:
   - GaussianBlur(gray, blurImg, Size(5,5), 0)
   - Neden Gaussian Blur uygulandığını yorumla.
     (İpucu: Gürültüyü azaltıp Canny için düzgün giriş hazırlar.)

4) Canny ile kenar bul:
   - threshold1 = 100
   - threshold2 = 200
   - Neden iki farklı eşik değeri kullanıldığını açıkla.
     (İpucu: Histerezis mantığı → güçlü kenarlar tutulur, zayıf olanlar bağlantılıysa eklenir.)

5) "Orijinal", "Gri", "Blur", "Canny" pencerelerini sırayla ekranda göster.

6) Kenar görüntüsünü "image_edges.jpg" olarak kaydet.

Aşağıdaki iskeleti tamamla:

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // 1) Oku

    // 2) Gri

    // 3) Gaussian Blur

    // 4) Canny edge

    // 5) Göster

    // 6) Kaydet

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

  // 2) Gri tona çevir
  // Kenar bulma algoritmaları tek kanallı (1-channel) görüntü ister,
  // çünkü gradyan hesapları 3 kanal üzerinde gereksiz karmaşıklık yaratır.
  cv::Mat gray;
  cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

  // 3) Gaussian Blur ile gürültüyü azalt
  // Canny, gürültüye çok hassastır. Bu yüzden öncesinde blur yapmak şarttır.
  cv::Mat blurImg;
  cv::GaussianBlur(gray, blurImg, cv::Size(5, 5), 0);

  // 4) Canny Edge Detection
  // threshold1 → zayıf kenarlar
  // threshold2 → güçlü kenarlar
  // Histerezis: güçlü kenara bağlı zayıf kenar da “kenar” kabul edilir.
  cv::Mat edges;
  cv::Canny(blurImg, edges, 100, 200);

  // 5) Hepsini ekranda göster
  cv::imshow("Orijinal", img);
  cv::imshow("Gri", gray);
  cv::imshow("Blur", blurImg);
  cv::imshow("Canny", edges);

  // 6) Kenar görüntüsünü diske kaydet
  cv::imwrite("image_edges.jpg", edges);

  cv::waitKey(0);
  cv::destroyAllWindows();
  return 0;
}
