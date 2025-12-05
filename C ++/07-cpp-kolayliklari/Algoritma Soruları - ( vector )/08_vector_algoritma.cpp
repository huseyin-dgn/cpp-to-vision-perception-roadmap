// 🔹 Soru – 10'dan kucuk olan tum elemanlari sil + kac tane silindi?
//
// 1) Kullanıcıdan n al.
// 2) n adet sayi oku ve vector<int> v icine push_back ile ekle.
// 3) Silmeden once, 10'dan kucuk kac eleman var?  --> count_if
//
//      std::count_if(v.begin(), v.end(), kosul);
//
// 4) Silme islemi: remove_if + erase
//
//      auto it = std::remove_if(
//              v.begin(), v.end(),
//              [](int x){ return x < 10; }
//      );
//      v.erase(it, v.end());
//
// 5) Final vector'u yazdir.
//
// Bu soru remove_if, lambda, count_if, begin/end araligi,
// hepsini sade bir sekilde ogrenmek icindir.

#include <iostream>
#include <vector>
#include <algorithm> // count_if, remove_if, erase

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

    // --- 3) Silinecek elemanlari say (x < 10)
    int silinecek = std::count_if(v.begin(), v.end(),
                                  [](int x)
                                  {
                                      return x < 10; // kosul
                                  });

    std::cout << "\n10'dan kucuk eleman sayisi: " << silinecek << "\n";

    // --- 4) Silme islemi: remove_if + erase
    auto it = std::remove_if(
        v.begin(), v.end(),
        [](int x)
        {
            return x < 10; // silme sartı
        });

    v.erase(it, v.end()); // cop bolgesini temizler

    // --- 5) Final vector'u yazdir
    std::cout << "Final vector (10'dan kucukler silindi): ";
    for (auto x : v)
    {
        std::cout << x << " ";
    }
    std::cout << "\n";

    return 0;
}
