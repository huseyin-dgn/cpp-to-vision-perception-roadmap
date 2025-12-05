// Soru:
//
// 1) Başlangıçta kapasitesi 2 olan bir dinamik dizi oluştur:
//
//
// 2) size = 0, capacity = 2 olsun.
//
// 3) Sırayla şu değerleri ekle: 10, 20, 30
//
//  - Eğer size < capacity ise:
//        arr[size] = değer;
//        size++;
//
//  - Eğer size == capacity ise:
//        kapasiteyi iki katına çıkar
//        (yeni array = new int[capacity * 2])
//        eski elemanları kopyala
//        eski array'i delete[] yap
//        arr pointer’ını yeni array’e ata
//
// 4) Sonuç olarak dizi şu olsun:
//        [10, 20, 30]
//
// 5) size ve capacity değerlerini ekrana yazdır.
//

#include <iostream>
#include <cstddef>

int main()
{
    int *arr = new int[2]; // kapasite = 2
    int size = 0;
    int capacity = 2;

    // Eklemek istediğimiz değerler
    int values[3] = {10, 20, 30};

    for (int v = 0; v < 3; v++)
    {
        int value = values[v];

        // Eğer dizi doluysa kapasiteyi artır
        if (size == capacity)
        {
            int newCapacity = capacity * 2;
            int *newArr = new int[newCapacity];

            // Eski elemanları kopyala
            for (int i = 0; i < size; i++)
            {
                newArr[i] = arr[i];
            }

            // Eski diziyi sil
            delete[] arr;

            // Yeni diziyi ata
            arr = newArr;
            capacity = newCapacity;
        }

        // Elemanı sona ekle
        arr[size] = value;
        size++;
    }

    // Sonuç dizisini yazdır
    std::cout << "Dizi elemanlari: ";
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    std::cout << "size = " << size << "\n";
    std::cout << "capacity = " << capacity << "\n";

    delete[] arr;
    return 0;
}
