// Soru: 7 - Dinamik Array
//
// 1) new int[5] ile 5 elemanlık bir dizi oluştur.
// 2) Bu diziye 0, 10, 20, 30, 40 değerlerini yerleştir.
// 3) Dizi elemanlarını ekrana yazdır.
// 4) delete[] ile belleği serbest bırak.
//
// Fonksiyon kullanmana gerek yok.
// Direkt main içinde yapabilirsin.

#include <iostream>
#include <cstddef>

int main()
{
    int *dizi = new int[5];

    for (std::size_t i = 0; i < 5; i++)
    {
        dizi[i] = i * 10;
    }

    for (std::size_t i = 0; i < 5; i++)
    {
        std::cout << "Dizi [ " << i << "]" << dizi[i] << "\n";
    }

    delete[] dizi;

    return 0;
}