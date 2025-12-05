// # 🔁 OpenCV Mini Tekrar Seti (Soru Bazlı)

// Aşağıdaki yapı tamamen **tekrar** için.
// Her bölümde:

// - Önce **kod + soru** var
// - Altında **kısa cevap / açıklama** var

// Hepsini tek tek çözmeye çalış, sonra cevap kısmından kontrol et.
// Amaç: “Bu satır ne yapıyor?” sorusunu beynine kazımak.

// ## 1️⃣ Temel Akış – imread, imshow, waitKey, imwrite //

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // S1: cv::Mat neyi temsil ediyor?
    cv::Mat img = cv::imread("test.jpg", cv::IMREAD_COLOR);

    // S2: imread başarısız olursa img.empty() ne döner?
    if (img.empty())
    {
        std::cout << "Goruntu yuklenemedi!\n";
        return -1;
    }

    // S3: imshow fonksiyonunun 1. ve 2. parametresi ne anlama geliyor?
    cv::imshow("Orijinal", img);

    // S4: waitKey(0) neden gerekli? Bunu silersek ne olur?
    cv::waitKey(0);

    // S5: imwrite ne iş yapar, aşağıdaki satır ne yapıyor?
    cv::imwrite("image_copy.jpg", img);

    cv::destroyAllWindows();
    return 0;
}

// ✅ Cevaplar

// S1: cv::Mat → OpenCV’nin görüntü matrisi; piksel verisini, boyutları, kanal sayısını vb. tutar.

// S2: true döner. Yani boş Mat; dosya okunamamıştır.

// S3: 1. parametre pencere adı (string), 2. parametre gösterilecek cv::Mat.

// S4: waitKey(0) yoksa pencere bir anda açılıp kapanır; event loop olmadığı için görüntüyü göremezsin.

// S5: image_copy.jpg isminde diske yeni bir dosya yazar; img’in içeriğini kaydeder.

// ## 2️⃣ Renkli → Gri – cvtColor, COLOR_BGR2GRAY ## //

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    cv::Mat img = cv::imread("test.jpg", cv::IMREAD_COLOR);
    if (img.empty())
        return -1;

    cv::Mat gray;

    // S1: Bu satır ne yapıyor? Hangi renk uzayından hangisine dönüştürüyor?
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    // S2: Gri görüntü kaç kanallıdır? (1 mi 3 mü?)
    // S3: Neden kenar bulma algoritmalarında genelde gri görüntü kullanıyoruz?

    cv::imshow("Orijinal", img);
    cv::imshow("Gri", gray);
    cv::waitKey(0);
    return 0;
}

// ✅ Cevaplar

// S1: BGR (3 kanallı renkli görüntü) → GRAY (1 kanallı gri görüntü) dönüşümü yapıyor.

// S2: 1 kanal.

// S3: Hesaplama daha basit; gradyan / kenar hesabı için renk bilgisine ihtiyaç yok, yoğunluk bilgisi yeterli.

// ## 3️⃣ Blur – GaussianBlur ## //

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    cv::Mat img = cv::imread("test.jpg");
    if (img.empty())
        return -1;

    cv::Mat blurImg;

    // S1: Bu satırdaki Size(5,5) neyi ifade ediyor?
    // S2: sigmaX = 0 ne demek?
    // S3: GaussianBlur neden gürültü azaltmak için kullanılır?
    cv::GaussianBlur(img, blurImg, cv::Size(5, 5), 0);

    cv::imshow("Orijinal", img);
    cv::imshow("Blur", blurImg);
    cv::waitKey(0);
    return 0;
}

// ✅ Cevaplar

// S1: 5x5 kernel; her piksel etrafındaki 5x5 komşuluk penceresiyle filtrelenir.

// S2: 0 → sigmaX’i kernel boyutundan otomatik hesapla demek.

// S3: Gaussian kernel merkezine daha çok, uzak piksellere daha az ağırlık verir; bu sayede rastgele gürültü yumuşatılır.

// ## 4️⃣ Binary Görüntü – threshold ## //

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    cv::Mat img = cv::imread("test.jpg", cv::IMREAD_GRAYSCALE);
    if (img.empty())
        return -1;

    cv::Mat binary;

    // S1: Bu satırdaki 100 ve 255 neyi ifade ediyor?
    // S2: THRESH_BINARY ne yapar?
    cv::threshold(img, binary, 100, 255, cv::THRESH_BINARY);

    cv::imshow("Gri", img);
    cv::imshow("Binary", binary);
    cv::waitKey(0);
    return 0;
}

// ✅ Cevaplar

// S1: 100 → eşik (threshold) değeri, 255 → beyaz değeri.

// S2: Piksel ≥ 100 ise 255 yapar (beyaz), piksel < 100 ise 0 yapar (siyah) → klasik siyah-beyaz görüntü.

// ## 5️⃣ Canny – Kenar Bulma ## //

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    cv::Mat img = cv::imread("test.jpg");
    if (img.empty())
        return -1;

    cv::Mat gray, blurImg, edges;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray, blurImg, cv::Size(5, 5), 0);

    // S1: Canny'nin 3. ve 4. parametreleri neyi ifade ediyor?
    // S2: Neden önce GaussianBlur yapıyoruz?
    cv::Canny(blurImg, edges, 100, 200);

    cv::imshow("Orijinal", img);
    cv::imshow("Canny", edges);
    cv::waitKey(0);
    return 0;
}

// ✅ Cevaplar

// S1: 100 → lower threshold, 200 → upper threshold (histerezis eşikleri).

// S2: Canny gürültüye hassas, blur ile gürültüyü azaltıp daha temiz kenarlar elde ediyoruz.

// ## 6️⃣ Sobel & Laplacian – Gradyan Tabanlı Kenar ## //

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    cv::Mat img = cv::imread("test.jpg");
    if (img.empty())
        return -1;

    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    cv::Mat sobelX, sobelY;
    // S1: CV_64F ne demek? Neden kullanıyoruz?
    // S2: (1,0) ve (0,1) neyi kontrol ediyor?
    cv::Sobel(gray, sobelX, CV_64F, 1, 0, 3);
    cv::Sobel(gray, sobelY, CV_64F, 0, 1, 3);

    cv::Mat sobelX_8, sobelY_8;
    cv::convertScaleAbs(sobelX, sobelX_8);
    cv::convertScaleAbs(sobelY, sobelY_8);

    cv::imshow("Sobel X", sobelX_8);
    cv::imshow("Sobel Y", sobelY_8);

    // Laplacian
    cv::Mat lap, lap_8;
    // S3: Laplacian ne tür bir türevdir (1. mi 2. mi?)
    cv::Laplacian(gray, lap, CV_64F);
    cv::convertScaleAbs(lap, lap_8);

    cv::imshow("Laplacian", lap_8);

    cv::waitKey(0);
    return 0;
}

// ✅ Cevaplar

// S1: CV_64F → 64-bit float; gradyan değerleri negatif/pozitif olabilir, taşma yaşamamak için kullanıyoruz.

// S2: (dx, dy):

// (1,0) → x yönünde türev (yatay kenarlar)

// (0,1) → y yönünde türev (dikey kenarlar)

// S3: Laplacian 2. türev; hem x hem y yönündeki değişimi birlikte yakalar.

// ## 7️⃣ Morfolojik İşlemler – Erosion, Dilation, Opening, Closing ## //

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    cv::Mat img = cv::imread("test.jpg", cv::IMREAD_GRAYSCALE);
    if (img.empty())
        return -1;

    cv::Mat binary;
    cv::threshold(img, binary, 128, 255, cv::THRESH_BINARY);

    // S1: Bu kernel neyi temsil ediyor?
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

    cv::Mat eroded, dilated, opening, closing;

    // S2: Erosion beyaz alanlara ne yapar?
    cv::erode(binary, eroded, kernel);

    // S3: Dilation beyaz alanlara ne yapar?
    cv::dilate(binary, dilated, kernel);

    // S4: Opening = hangi iki işlemin sırası?
    cv::morphologyEx(binary, opening, cv::MORPH_OPEN, kernel);

    // S5: Closing = hangi iki işlemin sırası?
    cv::morphologyEx(binary, closing, cv::MORPH_CLOSE, kernel);

    cv::imshow("Binary", binary);
    cv::imshow("Eroded", eroded);
    cv::imshow("Dilated", dilated);
    cv::imshow("Opening", opening);
    cv::imshow("Closing", closing);

    cv::waitKey(0);
    return 0;
}

// ✅ Cevaplar

// S1: 3x3 dikdörtgen yapı elemanı; morfolojik işlemlerde komşuluk maskesi.

// S2: Beyaz bölgeleri küçültür, ince kısımlar kaybolur → gürültü temizleme.

// S3: Beyaz bölgeleri büyütür, delikleri doldurur, kopuklukları birleştirebilir.

// S4: Opening = Erosion → Dilation (gürültü temizleme)

// S5: Closing = Dilation → Erosion (delik kapatma, nesneyi toparlama)

// ## 8️⃣ Contours + Bounding Box – findContours, boundingRect, rectangle ## //

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    cv::Mat img = cv::imread("image.jpg");
    if (img.empty())
        return -1;

    cv::Mat gray, blurImg, binary;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray, blurImg, cv::Size(5, 5), 0);
    cv::threshold(blurImg, binary, 100, 255, cv::THRESH_BINARY);

    // S1: Aşağıdaki yapı neyi temsil ediyor?
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    // S2: RETR_EXTERNAL ne demek?
    // S3: CHAIN_APPROX_SIMPLE ne işe yarar?
    cv::findContours(binary, contours, hierarchy,
                     cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    cv::Mat output = img.clone();

    for (size_t i = 0; i < contours.size(); ++i)
    {
        double area = cv::contourArea(contours[i]);
        // S4: Neden küçük alanları atıyoruz?
        if (area < 100.0)
            continue;

        // S5: boundingRect ne döner?
        cv::Rect bbox = cv::boundingRect(contours[i]);

        // S6: Bu satır ne çiziyor?
        cv::rectangle(output, bbox, cv::Scalar(0, 255, 0), 2);
    }

    cv::imshow("Binary", binary);
    cv::imshow("Bounding Box", output);
    cv::waitKey(0);
    return 0;
}

// ✅ Cevaplar

// S1:

// std::vector<std::vector<cv::Point>> contours; → her kontur, bir Point listesi; dış vektör = tüm konturlar.

// std::vector<cv::Vec4i> hierarchy; → her kontur için hiyerarşi bilgisi (parent, child, next, prev).

// S2: RETR_EXTERNAL → sadece dış konturları alır, iç halkaları görmezden gelir.

// S3: CHAIN_APPROX_SIMPLE → düz çizgiler üzerindeki gereksiz ara noktaları atar, konturu sadeleştirir.

// S4: Çok küçük konturlar genelde gürültü; onları işleme dahil etmek istemiyoruz.

// S5: cv::Rect döner (x, y, width, height) → o konturu içine alan en küçük dikdörtgen.

// S6: Orijinal görüntü üzerinde o dikdörtgeni yeşil kutu olarak çizer (kalınlık 2 px).