// 🔹 Soru  – Diziyi ters cevir, ilk/son elemani yer degistir, baska diziye sifir cek
//
// Kullanilacak hazir fonksiyonlar (toplam 5, bunun 3'u yeni):
//  - std::count        (Soru 1'den)
//  - std::find         (Soru 1'den)
//  - std::reverse      → diziyi ters cevir
//  - std::swap         → ilk ve son elemani yer degistir
//  - std::fill         → baska bir diziyi tek seferde doldur
//
// Görev:
//  - Kullanıcıdan n al (1–100).
//  - n adet tamsayi al ve arr[] dizisine koy.
//  - Kullanıcıdan x al.
//  - std::count ile x'in kac kez gectigini bul.
//  - std::find ile x'in ilk index'ini (varsa) bul.
//  - std::reverse(arr, arr+n) ile diziyi TERS cevir.
//  - std::swap(arr[0], arr[n-1]) ile ilk ve son elemani yer degistir.
//  - Yeni bir dizi brr[] tanimla (boyut 100) ve std::fill ile ilk n elemanini 0 yap.
//  - Hem arr[] (islenmis halini) hem de brr[]'yi ekrana yaz.
//
// Amaç: Hem onceki fonksiyonlarin tekrarini, hem de yeni 3 fonksiyonun kullanimini gormek.

#include <iostream>
#include <algorithm> // count, find, reverse, swap, fill

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
    int brr[100];

    std::cout << n << " adet tamsayi gir:\n";
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }

    int x;
    std::cout << "Aranacak sayiyi gir (x): ";
    std::cin >> x;

    // Soru 1'den: count + find
    int adet = std::count(arr, arr + n, x);
    int *p = std::find(arr, arr + n, x);

    std::cout << "\nSayi " << x << " dizide " << adet << " kez geciyor.\n";
    if (p != arr + n)
    {
        int index = p - arr;
        std::cout << "Ilk goruldugu index: " << index << "\n";
    }
    else
    {
        std::cout << "Bu sayi dizide yok.\n";
    }

    // std::reverse ile diziyi ters cevir
    std::reverse(arr, arr + n);

    // std::swap ile ilk ve son elemani yer degistir (n >= 2 ise)
    if (n >= 2)
    {
        std::swap(arr[0], arr[n - 1]);
    }

    // brr dizisinin ilk n elemanini 0 yap (fill)
    std::fill(brr, brr + n, 0);

    std::cout << "\nIslenmis arr (reverse + swap): ";
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    std::cout << "brr (fill ile sifirlanmis):   ";
    for (int i = 0; i < n; i++)
    {
        std::cout << brr[i] << " ";
    }
    std::cout << "\n";

    return 0;
}
