// Soru:
//
// 1) Başlangıçta şu dinamik diziyi oluştur:
//
//     int* arr = new int[6] { 1, 3, 3, 2, 3, 5 };
//
//     size = 6;
//     capacity = 6;
//
// 2) Diziden 3 değerine sahip TÜM elemanları sil.
//
// 3) Eleman silme işlemi şu şekilde olacak:
//     - 3 olmayan elemanları sola kaydır
//     - size'ı azalt
//
// 4) Sonuç şu olmalı:
//     [1, 2, 5]
//     size = 3
//     capacity = 6  (kapasite değişmez)
//
// 5) Son olarak dizinin yeni halini yazdır.
//
// Not:
//   - delete[] yapma, çünkü hala aynı buffer'ı kullanıyoruz.
//   - Tek işlemimiz size'ı değiştirmek.
//   - removeValue fonksiyonundaki two-pointer mantığı burada da geçerli.

#include <iostream>
#include <cstddef>

int main()
{
    int *arr = new int[6]{1, 3, 3, 2, 3, 5};
    int size = 6;
    int write = 0;

    for (std::size_t i = 0; i < size; i++)
    {
        if (arr[i] != 3)
        {
            arr[write] = arr[i];
            write++;
        }
    }

    size = write;

    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }

    std::cout << "\nsize = " << size << "\n";
    std::cout << "capacity = " << 6 << "\n";

    delete[] arr;

    return 0;
}