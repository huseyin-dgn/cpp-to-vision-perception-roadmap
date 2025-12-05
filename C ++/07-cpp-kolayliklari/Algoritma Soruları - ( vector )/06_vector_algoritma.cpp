// 🔹 Soru 2 – Vector'deki tekrar eden elemanlari sil (sort + unique)
//
// Görev:
//  1) Kullanıcıdan n al.
//  2) n tane tamsayi oku, std::vector<int> v icine push_back ile ekle.
//  3) v'yi std::sort ile sirala.
//  4) std::unique ile tekrar edenleri sıkıştır:
//         auto it = std::unique(v.begin(), v.end());
//     Bu islem, TEKIL degerleri basa toplar, geri kalan kisimi "cop" yapar.
//  5) v.erase(it, v.end()); ile bu cop kismi v'den tamamen sil.
//  6) Son halini ekrana yazdir.
//
// Ornek:
//   Girdi:  n = 7
//           5 3 3 10 10 10 2
//   Sirali: 2 3 3 5 10 10 10
//   Cikti:  2 3 5 10

#include <iostream>
#include <vector>
#include <algorithm> // sort, unique

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
    v.reserve(n); // opsiyonel

    std::cout << n << " adet tamsayi gir:\n";
    for (int i = 0; i < n; i++)
    {
        int x;
        std::cin >> x;
        v.push_back(x);
    }

    // 1) Siralama
    std::sort(v.begin(), v.end());

    std::cout << "\nSiralanmis vector: ";
    for (auto x : v)
    {
        std::cout << x << " ";
    }
    std::cout << "\n";

    // 2) unique ile tekrar edenleri sıkıştır
    auto it = std::unique(v.begin(), v.end());
    // it: tekil elemanlardan SONRAKI ilk cop konum

    // 3) erase ile cop bolgeyi kes
    v.erase(it, v.end());

    std::cout << "Tekillestirilmis vector (sort + unique + erase): ";
    for (auto x : v)
    {
        std::cout << x << " ";
    }
    std::cout << "\n";

    return 0;
}
