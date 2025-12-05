// 🔹 SORU – Closest Pair Sum
//
// İmza:
//
//     void closest_pair_sum(const int* arr, std::size_t n, int target,
//                           int& outA, int& outB);
//
// Görev:
//     - Dizideki iki elemanı seç.
//     - Bu iki elemanın toplamı "target" değerine EN YAKIN olsun.
//     - Bulduğun çifti outA ve outB'ye yaz.
//
// Örnek:
//     arr = [1, 4, 7, 12, 20]
//     target = 15
//
//     Mümkün çiftler ve toplamlar:
//         (1, 4)  = 5
//         (1, 7)  = 8
//         (4, 7)  = 11
//         (7, 12) = 19
//         (12,20) = 32
//
//     15'e en yakın toplam = 19  → çift = (7, 12)
//     sonuç: outA = 7, outB = 12
//
// Kurallar:
//     1) O(n²) brute force yapabilirsin (bizim şu anki seviyemiz için normal).
//     2) Diziyi sıralayıp iki-pointer ile O(n) yapmak da mümkün.
//     3) Ama önce brute force istiyorum.
//     4) abs(total - target) değerine göre yakınlık karşılaştır.
//     5) n < 2 ise hiçbir şey yapma.
//
// İpucu:
//     - minDiff = INT_MAX ile başla
//     - tüm çiftleri dene
//     - hedefe en yakın olanı güncelle

#include <iostream>
#include <cstddef>
#include <cstdlib> // abs
#include <climits> // INT_MAX

void closest_pair_sum(const int *arr, std::size_t n, int target,
                      int &outA, int &outB)
{
    if (n < 2)
        return; // çift seçilemez

    int minDiff = INT_MAX;

    for (std::size_t i = 0; i < n; ++i)
    {
        for (std::size_t j = i + 1; j < n; ++j)
        {
            int sum = arr[i] + arr[j];
            int diff = std::abs(sum - target);

            if (diff < minDiff)
            {
                minDiff = diff;
                outA = arr[i];
                outB = arr[j];
            }
        }
    }
}

int main()
{
    int arr[] = {1, 4, 7, 12, 20};
    std::size_t n = 5;

    int a = 0, b = 0;

    closest_pair_sum(arr, n, 15, a, b);

    std::cout << "En yakin çift: " << a << ", " << b << "\n";
}

// 🔥 Kısacık Açıklama

// Tüm çiftleri deniyoruz → O(n²).

// Her çiftin toplamı target’a ne kadar yakın → abs(sum - target)

// En küçük farkı görünce güncelliyoruz.

// Sonuç: target'a en yakın toplamı oluşturan iki sayı.