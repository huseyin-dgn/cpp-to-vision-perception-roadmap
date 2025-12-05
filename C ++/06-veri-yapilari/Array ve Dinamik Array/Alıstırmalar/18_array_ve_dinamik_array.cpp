// 🔹 Soru E – Dizideki Sıfırları Sona Taşı (in-place)
//
// İmza:
//
//     void move_zeros_to_end(int* arr, std::size_t n);
//
// Görev:
//
//   - Dizideki tüm **0** değerlerini sona taşı.
//   - 0 olmayan elemanlar ÖNDE kalacak.
//   - Elemanların kendi iç sırası ÖNEMLİ DEĞİL (yani stable olmak zorunda değil).
//   - Ekstra dizi kullanmak YASAK (in-place).
//
// Örnek:
//
//   arr = [0, 3, 0, 5, 1, 0, 4]
//   işlemden sonra:
//   arr = [3, 5, 1, 4, 0, 0, 0]
//
// Mantık:
//
//   ✔ Two-pointer (write index) mantığını kullanacağız.
//   ✔ "write" = 0’dan başlayarak 0 olmayan elemanları sola yaz.
//   ✔ döngü bittikten sonra kalan tüm elemanları 0 yap.
//
// Adımlar:
//
//   write = 0
//
//   for i = 0..n-1:
//       eğer arr[i] != 0 ise:
//           arr[write] = arr[i]
//           write++
//
//   // döngü bittiğinden write şu an 0 olmayan elemanların sayısı
//
//   for i = write..n-1:
//       arr[i] = 0
//
// ÖNEMLİ:
//
//   - 0 olmayan tüm elemanlar başa toplanır.
//   - Geri kalan pozisyonlar 0 yapılır.
//   - Ekstra array yok.
//   - Sıra bozulabiliyor, sorun değil.
//
// Kullanım:
//
//   int arr[] = {0, 3, 0, 5, 1, 0, 4};
//   move_zeros_to_end(arr, 7);
//   // arr artık [3,5,1,4,0,0,0]

#include <iostream>
#include <cstddef>

void move_zeros_to_end(int *arr, std::size_t n)
{
    std::size_t write = 0; // 0 olmayanların yazılacağı yer

    // 1) 0 olmayan elemanları başa topla
    for (std::size_t i = 0; i < n; ++i)
    {
        if (arr[i] != 0)
        {
            arr[write] = arr[i];
            write++;
        }
    }

    // 2) Geri kalan yerleri 0 yap
    for (std::size_t i = write; i < n; ++i)
    {
        arr[i] = 0;
    }
}
