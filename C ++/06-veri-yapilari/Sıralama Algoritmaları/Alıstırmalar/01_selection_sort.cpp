// Selection Sort algoritmasını yaz.
//
// Mantık:
//   - Diziyi soldan sağa dolaş
//   - Her pozisyon için, geri kalan elemanlar arasında EN KÜÇÜK olanı bul
//   - Bulduğun en küçük elemanı o pozisyondaki eleman ile yer değiştir
//
// Fonksiyon imzası:
//
//    void selection_sort(int arr[], int n);
//
// Görev:
//   - Dış döngü: i = 0'dan n-1'e kadar
//   - İç döngü: i+1'den n'e kadar min elemanı bul
//   - minIndex bulunduğunda arr[i] ile arr[minIndex] swap et
//
// Örnek:
//   int arr[] = {5, 2, 9, 1, 3};
//   selection_sort(arr, 5);
//
//   // sonuç: 1 2 3 5 9
//
// Kurallar:
//   - std::swap KULLANMA (kendi swap işlemini yaz)
//   - İç içe for döngüsü zorunlu
//   - minIndex tutmayı unutma
//   - Diziyi bozmadan min elemanı bul, sonra yer değiştir

#include <iostream>
#include <cstddef>

void selection_sort(int arr[], int n)
{
    for (std::size_t i = 0; i < static_cast<std::size_t>(n) - 1; i++)
    {
        std::size_t minIndex = i; // şu anki en küçük elemanın index'i

        // i+1'den sona kadar en küçüğü ara
        for (std::size_t a = i + 1; a < static_cast<std::size_t>(n); a++)
        {
            if (arr[a] < arr[minIndex])
            {
                minIndex = a;
            }
        }

        // bulduysan i ile minIndex'i swap et
        if (minIndex != i)
        {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}
