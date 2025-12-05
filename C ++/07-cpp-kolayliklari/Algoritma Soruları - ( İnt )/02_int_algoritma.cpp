// 🔹 Soru 3 – Stringten Sayıya, 3 Sayı Üzerinde Hesaplama ve Raporlama
//
// Bu soruda ŞU ANA KADAR öğrendiğimiz TÜM int araçlarını harmanlıyoruz.
//
// ZORUNLU ARAÇLAR:
//  - std::abs
//  - std::max
//  - std::min
//  - std::pow
//  - std::sqrt
//  - std::round
//  - %           (mod alma)
//  - std::to_string
//  - std::stoi
//
// Görev:
//
//  1) Kullanıcıdan önce string olarak bir sayı al (ör: "42").
//       std::string s_num;
//       std::getline(std::cin, s_num);
//
//  2) Bu string'i std::stoi ile tam sayıya çevir: x
//
//  3) Kullanıcıdan 2 tane daha tamsayı al: y, z.
//
//  4) Bu üç sayı (x, y, z) için şunları yap:
//
//     - En büyük sayıyı bul      → std::max
//     - En küçük sayıyı bul      → std::min
//     - Aralık = |max - min|     → std::abs
//     - En büyük sayının küpünü  → std::pow(max_val, 3)
//     - Aralığın karekökünü      → std::sqrt(range) (double)
//     - Üç sayının ortalamasını  → double avg = (x + y + z) / 3.0;
//       sonra std::round(avg) ile en yakın tam sayıya yuvarla.
//
//  5) x sayısı için:
//       - x % 2 == 0 → çift, değilse tek bilgisini ver.
//       - x % 3 ile 3'e bölümünden kalanı yaz.
//
//  6) Son olarak, std::to_string ile birkaç sonucu bir string'e çevirip
//     rapor satırı oluştur:
//       std::string rapor = "Max=" + to_string(max_val) + ", Min=" + ...;
//
//  7) Tüm sonuçları ekrana yaz.
//
// Örnek akış (örnek):
//   Girilen string sayi : "42"
//   x = 42, y = -5, z = 10
//   En buyuk          : 42
//   En kucuk          : -5
//   Aralik            : 47
//   Max'in kupu       : 74088
//   Aralik karekoku   : 6.85565...
//   Ortalama (double) : ...
//   Ortalama (round)  : ...
//   x cift mi / tek mi, x % 3 sonucu vs.
//   Rapor stringi     : Max=42, Min=-5, Range=47
// ----------------------------------------------------------------------

#include <iostream>
#include <string>
#include <algorithm> // std::max, std::min
#include <cstdlib>   // std::abs
#include <cmath>     // std::pow, std::sqrt, std::round

int main()
{
    // 1) String olarak sayi al
    std::string s_num;
    std::cout << "String olarak bir tamsayi gir (ornegin: 42): ";
    std::getline(std::cin, s_num);

    // 2) std::stoi ile string → int
    int x = 0;
    try
    {
        x = std::stoi(s_num);
    }
    catch (const std::exception &e)
    {
        std::cout << "Gecersiz sayi girisi! (stoi hata verdi)\n";
        return 1;
    }

    // 3) Iki sayi daha al
    int y, z;
    std::cout << "Iki tamsayi daha gir (y z): ";
    std::cin >> y >> z;

    // 4) max / min / aralik
    int max_xy = std::max(x, y);
    int max_xyz = std::max(max_xy, z);

    int min_xy = std::min(x, y);
    int min_xyz = std::min(min_xy, z);

    int range = std::abs(max_xyz - min_xyz);

    // max'in kupu (pow)
    double max_cube = std::pow(static_cast<double>(max_xyz), 3.0);

    // araligin karekoku (sqrt, range >= 0 zaten abs kullandik)
    double range_root = std::sqrt(static_cast<double>(range));

    // ortalama (double) ve round
    double avg = (x + y + z) / 3.0;
    int avg_rounded = static_cast<int>(std::round(avg));

    // 5) x icin mod islemleri
    bool x_is_even = (x % 2 == 0);
    int mod3 = x % 3;

    // 6) std::to_string ile rapor stringi
    std::string rapor = "Max=" + std::to_string(max_xyz) + ", Min=" + std::to_string(min_xyz) + ", Range=" + std::to_string(range);

    // 7) Sonuclari yazdir
    std::cout << "\n--- Hesap Sonuclari ---\n";
    std::cout << "x (stoi ile cevrilen) : " << x << "\n";
    std::cout << "y                     : " << y << "\n";
    std::cout << "z                     : " << z << "\n\n";

    std::cout << "En buyuk              : " << max_xyz << "\n";
    std::cout << "En kucuk              : " << min_xyz << "\n";
    std::cout << "Aralik (|max-min|)    : " << range << "\n";
    std::cout << "Max'in kupu           : " << max_cube << "\n";
    std::cout << "Aralik karekoku       : " << range_root << "\n";
    std::cout << "Ortalama (double)     : " << avg << "\n";
    std::cout << "Ortalama (round)      : " << avg_rounded << "\n\n";

    std::cout << "x cift mi?            : " << (x_is_even ? "EVET" : "HAYIR (TEK)") << "\n";
    std::cout << "x % 3                 : " << mod3 << "\n\n";

    std::cout << "Rapor stringi         : " << rapor << "\n";

    return 0;
}
