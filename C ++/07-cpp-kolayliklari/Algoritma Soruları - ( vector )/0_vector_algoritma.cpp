// 🔹 Soru  – Kullanıcıdan n adet sayı al ve vector'e ekle.
//              Ardından tüm elemanları tek tek yazdır.
//
// Amaç:
//  - vector nasıl tanımlanır?
//  - push_back nasıl çalışır?
//  - size() nedir?
//  - for(auto x : v) döngüsü nasıl işler?

#include <iostream>
#include <vector>

int main()
{
    int n;
    std::cout << "Kac sayi gireceksin? ";
    std::cin >> n;

    std::vector<int> v; // boş vector

    for (int i = 0; i < n; i++)
    {
        int x;
        std::cin >> x;
        v.push_back(x); // vector sona eleman ekler
    }

    std::cout << "\nVector elemanlari: ";
    for (auto x : v)
    { // range-based for
        std::cout << x << " ";
    }
    std::cout << "\n";

    return 0;
}
