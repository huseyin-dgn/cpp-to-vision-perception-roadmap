/*
🧩 SORU 3 – Gaussian Blur ile görüntüyü bulanıklaştır

Görevlerin:

1) Çalışma klasöründe bulunan "image.jpg" dosyasını oku.

2) Bu görüntüye Gaussian Blur uygula:
   - cv::GaussianBlur fonksiyonunu kullan.
   - 5x5 kernel (Size(5,5)) ve sigmaX = 0 parametrelerini kullan.
   - Gaussian Blur’un mantığını yorum satırıyla açıkla
       → Kenarlara daha az, merkeze daha çok ağırlık veren bir kernel kullanır.
       → Gürültüyü azaltır.

3) Hem orijinal görüntüyü hem de bulanık görüntüyü ekranda göster:
   - Pencere isimleri: "Orijinal", "Blur"

4) Bulanık görüntüyü "image_blur.jpg" olarak kaydet.

Aşağıdaki iskelet kodu tamamla:

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // 1) image.jpg oku

    // 2) GaussianBlur uygula

    // 3) Sonuçları göster

    // 4) Dosyaya kaydet

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
        std::cout << "Goruntu yuklenemedi!" << std::endl;
        return -1;
    }

    cv::Mat blurImg;

    // GaussianBlur:
    //  - 5x5 kernel: görüntünün her pikseli etrafındaki 5x5 komşuluk ile filtrelenir.
    //  - Merkeze daha fazla, kenarlara daha az ağırlık verilir (Gaussian dağılımı).
    //  - Gürültüyü azaltır, görüntüyü yumuşatır.
    cv::GaussianBlur(img, blurImg, cv::Size(5, 5), 0);

    cv::imshow("Orijinal", img);
    cv::imshow("Blur", blurImg);

    // Kaydet
    cv::imwrite("image_blur.jpg", blurImg);

    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}
