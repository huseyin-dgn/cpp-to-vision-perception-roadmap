// 🔹 Soru  – Vector'deki tum çift sayıları bul ve ikinci bir vector'e ekle.
//
// Amaç:
//  - vector içinde gezinmek
//  - şart kontrolü (x % 2 == 0)
//  - yeni bir vector oluşturup push_back ile veri taşımak

#include <iostream>
#include <vector>

int main()
{
    int n;
    std::cout << "Kac sayi gireceksin? ";
    std::cin >> n;

    std::vector<int> v;
    std::vector<int> ciftler; // sadece çiftleri tutan vector

    for (int i = 0; i < n; i++)
    {
        int x;
        std::cin >> x;
        v.push_back(x);
    }

    for (auto x : v)
    {
        if (x % 2 == 0)
        {
            ciftler.push_back(x);
        }
    }

    std::cout << "\nCift sayilar: ";
    for (auto x : ciftler)
    {
        std::cout << x << " ";
    }
    std::cout << "\n";

    return 0;
}
