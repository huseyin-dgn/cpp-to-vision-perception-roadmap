// 🔹 Soru – Vector'deki NEGATIF sayilari sil + kac tane olduklarini yaz
//
// 1) Kullanıcıdan n al.
// 2) n tane sayı oku ve vector<int> v içine push_back ile ekle.
// 3) Negatif sayilarin sayisini count_if ile bul.
// 4) Negatif sayilari remove_if + erase ile sil.
// 5) Final vector'u yazdir.
//
// Kullanilan modern C++ kavramlari:
//   - count_if
//   - remove_if
//   - lambda ([](int x){ ... })
//   - erase (remove-erase idiomu)

#include <iostream>
#include <vector>
#include <algorithm> // count_if, remove_if

int main()
{
    int n;
    std::cout << "Kac eleman gireceksin? ";
    std::cin >> n;

    std::vector<int> v;
    v.reserve(n);

    std::cout << n << " adet sayi gir:\n";
    for (int i = 0; i < n; i++)
    {
        int x;
        std::cin >> x;
        v.push_back(x);
    }

    // 1) Negatiflerin sayisini bul
    int negSayisi = std::count_if(v.begin(), v.end(),
                                  [](int x)
                                  {
                                      return x < 0; // negatif mi?
                                  });

    std::cout << "\nNegatif eleman sayisi: " << negSayisi << "\n";

    // 2) Negatifleri silmek
    auto it = std::remove_if(v.begin(), v.end(),
                             [](int x)
                             {
                                 return x < 0; // negatifleri sil
                             });

    v.erase(it, v.end()); // cop bolgesini at

    // 3) Final vector'u yazdir
    std::cout << "Negatifler silindikten sonra vector: ";
    for (auto x : v)
    {
        std::cout << x << " ";
    }
    std::cout << "\n";

    return 0;
}
