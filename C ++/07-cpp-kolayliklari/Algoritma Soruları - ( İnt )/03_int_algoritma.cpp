// 🔹 Soru – Dizide Toplam, Ortalama, Min, Max (std::accumulate + std::sort)
//
// Kullanılacak araçlar (zorunlu):
//  - int ve C tarzı dizi (int arr[...])
//  - std::accumulate  → dizinin toplamını almak için
//  - std::sort        → diziyi artan sırada sıralamak için
//
// Görev:
//  - Kullanıcıdan n al (1 ile 100 arasında).
//  - n tane tamsayı oku, arr[] dizisine doldur.
//  - std::accumulate ile dizinin toplamını hesapla.
//  - Toplamdan yola çıkarak ortalamayı double olarak hesapla.
//  - std::sort ile diziyi artan sırada sırala.
//  - Sıralanmış diziyi ekrana yazdır.
//  - En küçük elemanı (arr[0]) ve en büyük elemanı (arr[n-1]) ekrana yaz.
//
// Örnek:
//   Girdi: n = 5, dizi = [3, -1, 10, 4, 2]
//   Siralanmis: -1 2 3 4 10
//   Toplam: 18
//   Ortalama: 3.6
//   En kucuk: -1
//   En buyuk: 10

#include <iostream>
#include <algorithm> // std::sort
#include <numeric>   // std::accumulate

int main()
{
    int n;
    std::cout << "Kac eleman gireceksin? ";
    std::cin >> n;

    if (n <= 0 || n > 100)
    {
        std::cout << "n 1 ile 100 arasinda olmali.\n";
        return 1;
    }

    int arr[100];

    std::cout << n << " adet tamsayi gir:\n";
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }

    // std::accumulate ile toplam:
    //  - arr      : baslangic adresi
    //  - arr + n  : bitis adresi (son elemandan 1 sonrasi)
    //  - 0        : toplam baslangic degeri
    int sum = std::accumulate(arr, arr + n, 0);

    double avg = sum / static_cast<double>(n);

    // std::sort ile siralama (artan)
    std::sort(arr, arr + n);

    std::cout << "\nSiralanmis dizi: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    int min_val = arr[0];
    int max_val = arr[n - 1];

    std::cout << "Toplam    : " << sum << "\n";
    std::cout << "Ortalama  : " << avg << "\n";
    std::cout << "En kucuk  : " << min_val << "\n";
    std::cout << "En buyuk  : " << max_val << "\n";

    return 0;
}
