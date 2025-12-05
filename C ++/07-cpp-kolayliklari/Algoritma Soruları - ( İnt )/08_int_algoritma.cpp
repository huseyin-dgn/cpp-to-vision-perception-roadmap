// 🔹 Soru 3 – Sirali dizide eleman arama ve EBOB/EKOK hesaplama
//
// Kullanilacak hazir fonksiyonlar:
//  - std::count         (Soru 1'den)
//  - std::find          (Soru 1'den)
//  - std::reverse       (Soru 2'den, istersek yeniden kullaniriz)
//  - std::swap          (Soru 2'den, gerekirse kullaniriz)
//  - std::fill          (Soru 2'den, gerekirse kullaniriz)
//  - std::binary_search → SIRALI dizide x var mi yok mu, hizlica kontrol
//  - std::gcd           → a ve b sayilarinin EBOB'u
//  - std::lcm           → a ve b sayilarinin EKOK'u
//
// Görev:
//  - Kullanıcıdan n al (1–100).
//  - n adet tamsayi al ve arr[] dizisine koy.
//  - Diziyi std::sort ile artan sekilde sirala (binary_search icin gerekli).
//  - Kullanıcıdan x al.
//  - std::binary_search(arr, arr+n, x) ile x dizide var mi, bak.
//  - Ayrica std::count ile x kac kez geciyor, onu da yaz.
//  - std::find ile x'in ilk index'ini (varsa) cikart.
//  - Siralanmis dizide en kucuk = arr[0], en buyuk = arr[n-1] olsun.
//  - Bu iki sayinin EBOB ve EKOK'unu std::gcd ve std::lcm ile hesapla.
//  - Tum sonuclari ekrana yaz.
//
// Not: EBOB/EKOK icin n >= 2 olmasi daha mantikli.

#include <iostream>
#include <algorithm> // sort, count, find, binary_search
#include <numeric>   // gcd, lcm

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

    // Siralama (binary_search icin gerekli)
    std::sort(arr, arr + n);

    std::cout << "\nSiralanmis dizi: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    int x;
    std::cout << "Aranacak sayiyi gir (x): ";
    std::cin >> x;

    // binary_search ile var mi yok mu?
    bool var_mi = std::binary_search(arr, arr + n, x);

    // count ile kac kez geciyor?
    int adet = std::count(arr, arr + n, x);

    // find ile ilk index
    int *p = std::find(arr, arr + n, x);

    std::cout << "\nSayi " << x << " dizide "
              << (var_mi ? "VAR" : "YOK") << ".\n";
    std::cout << "Gecis sayisi (count): " << adet << "\n";

    if (p != arr + n)
    {
        int index = p - arr;
        std::cout << "Ilk goruldugu index: " << index << "\n";
    }
    else
    {
        std::cout << "Bu sayi hic gecmiyor.\n";
    }

    if (n >= 2)
    {
        int min_val = arr[0];
        int max_val = arr[n - 1];

        int ebob = std::gcd(min_val, max_val);
        int ekok = std::lcm(min_val, max_val);

        std::cout << "\nEn kucuk eleman: " << min_val << "\n";
        std::cout << "En buyuk eleman : " << max_val << "\n";
        std::cout << "EBOB(min,max)   : " << ebob << "\n";
        std::cout << "EKOK(min,max)   : " << ekok << "\n";
    }
    else
    {
        std::cout << "\nEBOB/EKOK icin en az 2 eleman lazim.\n";
    }

    return 0;
}
