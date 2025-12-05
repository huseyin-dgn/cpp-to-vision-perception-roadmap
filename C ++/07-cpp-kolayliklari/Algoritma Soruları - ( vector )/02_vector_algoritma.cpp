// 🔹 Soru – Vector'deki elemanların ortalamasını hesapla.
//
// Amaç:
//  - size() ile eleman sayısına erişme
//  - index ile erişim (v[i])
//  - int toplam alıp double bölme

#include <iostream>
#include <vector>

int main()
{
    int n;
    std::cout << "Kac sayi gireceksin ;";
    std::cin >> n;

    std::vector<int> v;

    for (int i = 0; i < n; i++)
    {
        int x;
        std::cin >> x;
        v.push_back(x);
    }

    int sum = 0;
    for (int i = 0; i < v.size(); i++)
    {
        sum += v[i];
    }

    double avg = sum / static_cast<double>(v.size());

    std::cout << "\nOrtalama" << avg << "\n";

    return 0;
}