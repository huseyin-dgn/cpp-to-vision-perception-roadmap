// 🔹 Soru  – std::accumulate ve std::sort ile hizli istatistik
//
// Yeni ogrenecegimiz hazir fonksiyonlar:
//  - std::accumulate (dizinin toplamini almak icin)
//  - std::sort       (diziyi siralamak icin)
//
// Görev:
//  - Kullanıcıdan n al (1–100).
//  - n tane tamsayi oku, arr[] dizisine doldur.
//  - std::accumulate ile toplam bul.
//  - Ortalamayi double olarak hesapla.
//  - std::sort ile diziyi sirala (artan).
//  - Siralanmis diziyi yazdir.
//  - En kucuk = arr[0], en buyuk = arr[n-1] olarak ekrana yaz.

#include <iostream>
#include <algorithm>
#include <cstddef>
#include <numeric>

int main()
{
    int n;
    std::cout << "Kac eleman gireceksin ; ";
    std::cin >> n;

    if (n <= 0 || n > 100)
    {
        std::cout << "n 1 ile 100 arasında olmali";
        return 1;
    }

    int arr[100];
    std::cout << "n adet tam sayı gir \n";
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }

    int sum = std::accumulate(arr, arr + n, 0);

    double avg = sum / static_cast<double>(n);

    std::sort(arr, arr + n);

    std::cout << "\nSiralanmis dizi: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
}