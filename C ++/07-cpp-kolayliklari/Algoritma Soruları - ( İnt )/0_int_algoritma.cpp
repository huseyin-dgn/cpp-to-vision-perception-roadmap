// 🔹 Soru 1 – Üç sayının en büyüğü, en küçüğü ve aralığı
//
// Kullanılacak araçlar (zorunlu):
//  - std::abs   (mutlak değer)
//  - std::max  (en büyük)
//  - std::min  (en küçük)
//
// Görev:
//  - Kullanıcıdan 3 adet tamsayı al: a, b, c.
//  - Bu üç sayı içinden:
//      * En büyük sayıyı bul (std::max kullanarak).
//      * En küçük sayıyı bul (std::min kullanarak).
//      * En büyük ile en küçük arasındaki farkın mutlak değerini hesapla
//        (std::abs ile).
//  - Sonuçları ekrana yazdır.
//
// Örnek:
//   Girdi:  a = -5, b = 10, c = 3
//   En buyuk: 10
//   En kucuk: -5
//   Aralik (|max - min|): 15

#include <iostream>
#include <algorithm> // std::max, std::min
#include <cstdlib>   // std::abs

int main()
{
    int a, b, c;

    std::cout << "Uc tamsayi gir (a b c): ";
    std::cin >> a >> b >> c;

    // En buyuk degeri bulmak icin std::max'i iki kez kullaniyoruz.
    int max_ab = std::max(a, b);       // a ve b'nin en buyugu
    int max_abc = std::max(max_ab, c); // (a,b)'nin en buyugu ile c'nin en buyugu

    // En kucuk degeri bulmak icin std::min'i iki kez kullaniyoruz.
    int min_ab = std::min(a, b);       // a ve b'nin en kucugu
    int min_abc = std::min(min_ab, c); // (a,b)'nin en kucugu ile c'nin en kucugu

    // Aralik = |max - min|
    int range = std::abs(max_abc - min_abc);

    std::cout << "En buyuk  : " << max_abc << "\n";
    std::cout << "En kucuk  : " << min_abc << "\n";
    std::cout << "Aralik    : |max - min| = " << range << "\n";

    return 0;
}
