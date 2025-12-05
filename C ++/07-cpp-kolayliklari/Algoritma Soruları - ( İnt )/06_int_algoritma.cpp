// 🔹 Soru  – Bir sayinin dizide kac kez gectigini ve ilk index'ini bul
//
// Kullanilacak hazir fonksiyonlar (2 adet):
//  - std::count   → dizideki x degerinin kac kez gectigini say
//  - std::find    → dizide x'in ilk goruldugu yeri bul (adres)
//
// Görev:
//  - Kullanıcıdan n al (1–100).
//  - n adet tamsayi al ve arr[] dizisine koy.
//  - Kullanıcıdan bir tamsayi x al.
//  - std::count(arr, arr+n, x) ile x'in kac kere gectigini bul.
//  - std::find(arr, arr+n, x) ile x ilk nerede gorunuyor, index olarak yaz.
//    * Eger std::find sonucu arr+n ise: x bulunamadi de.
//  - Sonuclari ekrana yaz.
//
// Örnek:
//   n = 6, arr = [3, 5, 3, 7, 3, 9], x = 3
//   count = 3
//   ilk index = 0
//   (x = 8 olsaydi: count = 0, "dizide yok" yazacaktik)

#include <iostream>
#include <algorithm> // std::count, std::find

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

    int x;
    std::cout << "Aranacak sayiyi gir (x): ";
    std::cin >> x;

    // x kac kez geciyor?
    int adet = std::count(arr, arr + n, x);

    // x ilk nerede gorunuyor?
    int *p = std::find(arr, arr + n, x);

    std::cout << "\nSayi " << x << " dizide " << adet << " kez geciyor.\n";

    if (p != arr + n)
    {
        int index = p - arr; // pointer aritmetigi, kac eleman ilerideyse o index
        std::cout << "Ilk goruldugu index: " << index << "\n";
    }
    else
    {
        std::cout << "Bu sayi dizide yok.\n";
    }

    return 0;
}
