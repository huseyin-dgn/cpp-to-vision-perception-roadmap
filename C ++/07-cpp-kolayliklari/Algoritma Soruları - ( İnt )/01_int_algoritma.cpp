// 🔹 Soru 2 – 3 Sayı Üzerinde İstatistik ve Hesaplama
//
// Bu soruda hem ilk 3 fonksiyonu HEM de yeni 3 fonksiyonu kullanacağız:
//
// ZORUNLU ARAÇLAR:
//  - std::abs   (mutlak değer)
//  - std::max   (en büyük)
//  - std::min   (en küçük)
//  - std::pow   (üs alma)
//  - std::sqrt  (karekök)
//  - std::round (yuvarlama)
//
// Görev:
//  - Kullanıcıdan 3 adet tamsayı al: a, b, c.
//  - 1) Bu üç sayı içinden:
//       * En büyük sayıyı bul (std::max ile).
//       * En küçük sayıyı bul (std::min ile).
//       * max ve min arasındaki farkın mutlak değerini hesapla (std::abs).
//
//  - 2) En büyük sayının karesini hesapla:
//       * double max_sq = std::pow(max_abc, 2);
//
//  - 3) max ve min arasındaki farkın karekökünü hesapla:
//       * double root = std::sqrt( std::abs(max_abc - min_abc) );
//       * sqrt negatif istemez, o yüzden önce abs kullan.
//
//  - 4) Üç sayının ortalamasını double olarak hesapla, sonra std::round ile
//       en yakın tam sayıya yuvarla:
//       * double avg = (a + b + c) / 3.0;
//       * long long avg_rounded = std::llround(avg);  // veya (int)std::round(avg);
//
//  - 5) Tüm bu sonuçları ekrana yazdır.
//
// Örnek:
//   Girdi:  a = -5, b = 10, c = 3
//   En buyuk       : 10
//   En kucuk       : -5
//   Aralik         : 15
//   En buyugun karesi      : 100
//   Aralik karekoku        : sqrt(15) ≈ 3.87
//   Ortalama (double)      : 2.666...
//   Ortalama (yuvarlanmis) : 3

#include <iostream>
#include <algorithm> // std::max, std::min
#include <cstdlib>   // std::abs
#include <cmath>     // std::pow, std::sqrt, std::round, std::llround

int main()
{
    int a, b, c;

    std::cout << "Uc tamsayi gir (a b c): ";
    std::cin >> a >> b >> c;

    // --- 1) max ve min bulma (std::max, std::min) ---

    int max_ab = std::max(a, b);
    int max_abc = std::max(max_ab, c);

    int min_ab = std::min(a, b);
    int min_abc = std::min(min_ab, c);

    int range = std::abs(max_abc - min_abc); // mutlak fark

    // --- 2) max'in karesi (std::pow) ---

    double max_sq = std::pow(static_cast<double>(max_abc), 2.0);

    // --- 3) araligin karekoku (std::sqrt + std::abs) ---

    double root = std::sqrt(static_cast<double>(range));

    // --- 4) ortalama ve yuvarlama (std::round / std::llround) ---

    double avg = (a + b + c) / 3.0;            // double ortalama
    long long avg_rounded = std::llround(avg); // en yakin tam sayiya yuvarla

    // --- 5) Sonuclari yazdir ---

    std::cout << "En buyuk            : " << max_abc << "\n";
    std::cout << "En kucuk            : " << min_abc << "\n";
    std::cout << "Aralik (|max-min|)  : " << range << "\n";
    std::cout << "En buyugun karesi   : " << max_sq << "\n";
    std::cout << "Aralik karekoku     : " << root << "\n";
    std::cout << "Ortalama (double)   : " << avg << "\n";
    std::cout << "Ortalama (yuvarli)  : " << avg_rounded << "\n";

    return 0;
}
