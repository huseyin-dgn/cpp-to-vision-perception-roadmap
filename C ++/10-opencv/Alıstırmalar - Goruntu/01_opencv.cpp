/*
🧩 SORU 2 – Renkli Görüntüyü Gri Tona Çevirme ve Kaydetme

Görevlerin:

1) Çalışma klasöründe bulunan "image.jpg" dosyasını oku.
   - cv::Mat kullanarak oku.
   - imread fonksiyonunu IMREAD_COLOR ile kullan.

2) Bu görüntüyü gri tona çevir:
   - cvtColor fonksiyonunu kullan.
   - COLOR_BGR2GRAY sabitinin ne yaptığını yorum satırında açıkla.

3) Hem orijinal renkli görüntüyü hem de gri görüntüyü ayrı pencerelerde göster:
   - "Orijinal" ve "Gri" isimli pencereler kullan.

4) Gri görüntüyü "image_gray.jpg" adıyla diske kaydet:
   - imwrite fonksiyonunu kullan.

Teorik bilgi (yorum satırı olarak eklemen isteniyor):

- Gri ton hesabı kabaca şu formüle dayanır:
    Gray = 0.299*R + 0.587*G + 0.114*B
  (İnsan gözü yeşile daha duyarlı olduğu için G katsayısı daha büyüktür.)

Aşağıdaki iskelet main fonksiyonunu KENDİN DOLDUR:

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // 1) image.jpg dosyasını oku


    // 2) Gri tona çevir (cvtColor + COLOR_BGR2GRAY)


    // 3) Orijinal ve gri görüntüyü göster


    // 4) Gri görüntüyü image_gray.jpg olarak kaydet


    // 5) Tuş bekle, pencereleri kapat


    return 0;
}
*/

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    cv::Mat img = cv::imread("test.jpg", cv::IMREAD_COLOR);

    if (img.empty())
    {
        std::cout << "Goruntu Yuklenmedi...";
        return -1;
    }

    cv::Mat Gray;
    cv::cvtColor(img, Gray, cv::COLOR_BGR2GRAY);

    cv::imshow("Orijinal", img);
    cv::imshow("Gri", Gray);

    if (!cv::imwrite("image_gray.jpg", Gray))
    {
        std::cout << "Gri goruntu diske kaydedilmedi";
    }

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}