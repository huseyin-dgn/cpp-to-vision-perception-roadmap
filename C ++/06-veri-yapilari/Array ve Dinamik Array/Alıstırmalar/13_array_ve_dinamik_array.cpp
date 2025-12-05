// 🔹 SORU: max_subarray_sum (Brute Force)
//
// Elinde int dizisi var:
//
//   int* arr = new int[6] { -2, 3, -1, 5, -3, 2 };
//   std::size_t n = 6;
//
// Görev:
//   Aşağıdaki imzaya sahip fonksiyonu yaz:
//
//   int max_subarray_sum(const int* arr, std::size_t n);
//
// Tanım:
//   "Alt dizi" = dizinin ardışık elemanlarından oluşan parça.
//
//   Örnek alt diziler:
//     [3]
//     [3, -1, 5]
//     [-1, 5, -3]
//     [3, -1, 5, -3, 2]  vs.
//
// İstenen:
//   - Tüm mümkün alt diziler içinden,
//     toplamı EN BÜYÜK olan alt dizinin toplamını döndür.
//
// Örnek:
//   arr = [-2, 3, -1, 5, -3, 2]
//
//   Alt dizilerden bazıları:
//     [3]           → toplam = 3
//     [3, -1, 5]    → toplam = 7
//     [3, -1, 5, -3, 2] → toplam = 6
//     [5]           → toplam = 5
//
//   En büyük toplam = 7  ( [3, -1, 5] )
//
// Kurallar:
//
// 1) Brute force yaz: O(n^2) olması yeterli.
//    - Dış döngü: alt dizinin başlangıç index'i (start)
//    - İç döngü: alt dizinin bitiş index'i (end)
//    - "running sum" ile start..end arasını topla.
//
// 2) n == 0 ise:
//      istersen özel olarak 0 dönebilirsin.
//
// İmza tekrar:
//
//   int max_subarray_sum(const int* arr, std::size_t n);
//

#include <iostream>
#include <cstddef>

int max_subarray_sum(const int *arr, std::size_t n)
{
    if (n == 0)
    {
        return 0; // boş dizi durumu
    }

    int max_sum = arr[0]; // şimdilik en iyi toplam

    for (std::size_t start = 0; start < n; ++start)
    {
        int current_sum = 0; // start'tan başlayan alt dizinin toplamı

        for (std::size_t end = start; end < n; ++end)
        {
            current_sum += arr[end]; // start..end aralığını büyütüyoruz

            if (current_sum > max_sum)
            {
                max_sum = current_sum; // daha iyi bir toplam bulduk
            }
        }
    }

    return max_sum;
}

int main()
{
    int arr[6] = {-2, 3, -1, 5, -3, 2};
    std::size_t n = 6;

    int result = max_subarray_sum(arr, n);
    std::cout << "Max subarray sum = " << result << "\n";

    return 0;
}

// Mantığı kısa özet:

// start → alt dizinin başlangıcı

// end → alt dizinin bitişi

// Her start için:

// current_sum = 0

// end’i start’tan n-1’e kadar yürüt:

// current_sum += arr[end]

// her adımda current_sum ile max_sum’ı kıyasla