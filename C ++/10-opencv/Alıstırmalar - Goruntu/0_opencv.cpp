/*
🧩 SORU 1 – OpenCV ile Temel Görüntü Okuma ve Gösterme

Görevlerin:

1) Çalışma klasöründe bulunan "image.jpg" dosyasını diskin üzerinden oku
   - cv::Mat kullanarak oku.
   - imread fonksiyonunun 2. parametresi olan "flags" (ör: IMREAD_COLOR) ne işe yarar, yorum satırında kısaca açıklayın.

2) Okuma işlemi başarısızsa:
   - img.empty() kontrolü yap.
   - Ekrana "Goruntu yuklenemedi!" şeklinde bir hata mesajı yaz.
   - Programı -1 ile bitir.

3) Okuma başarılıysa:
   - Görüntüyü "Orijinal" adlı bir pencerede göster (imshow).
   - Kullanıcı bir tuşa basana kadar bekle (waitKey).

4) Program biterken:
   - Tüm pencereleri kapat (destroyAllWindows veya sadece return ile çık; ikisinden birini seçip nedenini yorum satırında belirt).

Açıklaman gerekenler (yorum satırı olarak kısa kısa yaz):

- cv::Mat nedir, neyi temsil eder?
- imread ne döner, başarısız olursa ne olur?
- imshow ve waitKey fonksiyonlarının mantığı nedir?

Aşağıdaki main fonksiyonunu KENDİN TAMAMLA.
Çözümü bir sonraki adımda birlikte kontrol edeceğiz.
*/

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
   // cv::Mat: OpenCV'nin temel görüntü veri yapısı.
   // Piksel verisini + yüksekliği + genişliği + kanal sayısını vs. içinde tutar.

   // imread:
   //  - 1. parametre: dosya yolu
   //  - 2. parametre: okuma modu (flags)
   //      IMREAD_COLOR    → Renkli oku (BGR, 3 kanal) - varsayılan
   //      IMREAD_GRAYSCALE→ Gri tonlu oku (1 kanal)
   //      IMREAD_UNCHANGED→ Alfa kanalı varsa onu da koru (4 kanal)
   cv::Mat img = cv::imread("test.jpg",
                            cv::IMREAD_COLOR);

   // imread başarısız olursa (dosya yok, yol yanlış, format bozuk vs.)
   // img.empty() true döner → içeride veri yok demektir.
   if (img.empty())
   {
      std::cout << "Goruntu yuklenemedi!" << std::endl;
      return -1; // hata kodu ile çık
   }

   // imshow:
   //  - 1. parametre: pencere adı
   //  - 2. parametre: gösterilecek Mat
   cv::imshow("Orijinal", img);

   // waitKey:
   //  - pencerenin ekranda kalmasını sağlar (event loop gibi düşün)
   //  - 0 → sonsuza kadar tuş bekle
   //  - >0 → milisaniye cinsinden süre bekler
   cv::waitKey(0);

   // destroyAllWindows:
   //  - Tüm OpenCV pencerelerini kapatır.
   //  - Zorunlu değil, program zaten bitiyor ama temiz çıkış için iyi alışkanlık.
   cv::destroyAllWindows();

   return 0;
}
