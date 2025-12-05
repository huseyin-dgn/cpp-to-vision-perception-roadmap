// 🔹 Soru  Vector'deki elemanlari analiz et ve hepsini +5 arttir
//
// Görev:
//  1) Kullanıcıdan n al (pozitif).
//  2) n tane tamsayi oku ve std::vector<int> v içine push_back ile ekle.
//  3) Aşağıdakileri yap:
//
//     a) Klasik for ile (i = 0..size-1):
//          - her elemanın index ve degerini yazdır
//          - toplamı hesapla
//     b) Ayrı bir döngüde (yine index ile):
//          - en küçük ve en büyük elemanı bul (std::min/max YOK, kendin if ile)
//     c) Range-based for + referans (for (auto& x : v)) kullanarak:
//          - her elemanı 5 arttır (x = x + 5)
//     d) Son olarak vector'ü tekrar yaz:
//          - "Guncellenmis vector:" diye başlık at
//
// Amaç:
//  - v.size() + v[i] ile index tabanlı gezinme
//  - toplam / min / max hesaplamayı elle yapmak
//  - for (auto& x : v) ile vector içini DIREKT değiştirmeyi görmek

#include <iostream>
#include <vector>

int main()
{
    int n;
    std::cout << "Kac eleman gireceksin? ";
    std::cin >> n;

    if (n <= 0)
    {
        std::cout << "Pozitif bir n lazim.\n";
        return 1;
    }

    std::vector<int> v;
    v.reserve(n); // opsiyonel: performans icin

    std::cout << n << " adet tamsayi gir:\n";
    for (int i = 0; i < n; i++)
    {
        int x;
        std::cin >> x;
        v.push_back(x);
    }

    // a) index ile gez, yazdir ve toplam al
    int sum = 0;

    std::cout << "\n[1] Index ile erisim ve toplam alma:\n";
    for (int i = 0; i < static_cast<int>(v.size()); i++)
    {
        std::cout << "index " << i << " -> " << v[i] << "\n";
        sum += v[i];
    }

    std::cout << "Toplam: " << sum << "\n";

    // b) min ve max'i elle bul
    int min_val = v[0];
    int max_val = v[0];

    for (int i = 1; i < static_cast<int>(v.size()); i++)
    {
        if (v[i] < min_val)
        {
            min_val = v[i];
        }
        if (v[i] > max_val)
        {
            max_val = v[i];
        }
    }

    std::cout << "En kucuk: " << min_val << "\n";
    std::cout << "En buyuk: " << max_val << "\n";

    // c) range-based for + referans ile HER elemani +5
    for (auto &x : v)
    { // x, v icindeki elemanin kendisi (kopya degil)
        x = x + 5;
        // alternatif kisaltma: x += 5;
    }

    // d) guncellenmis vector'u yaz
    std::cout << "\n[2] Guncellenmis vector (her eleman +5): ";
    for (auto x : v)
    { // burada kopya yeterli, sadece yazdiriyoruz
        std::cout << x << " ";
    }
    std::cout << "\n";

    return 0;
}
