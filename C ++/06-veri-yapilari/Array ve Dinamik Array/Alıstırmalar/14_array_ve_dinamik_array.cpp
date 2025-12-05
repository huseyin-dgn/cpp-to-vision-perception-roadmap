// 🔹 Soru X – Dizideki İkinci En Büyük Elemanı Bul
//
// İmza:
//
//     int second_largest(const int* arr, std::size_t n);
//
// İstenen:
//
// - arr dizisinde **en büyük ikinci** sayıyı bul ve döndür.
// - Eğer ikinci en büyük YOKSA (örneğin:
//      * n < 2 ise
//      * veya tüm elemanlar birbirine eşitse)
//   bu durumda **-1** döndür.
//
// Kurallar:
//
// - Zaman karmaşıklığı O(n) olsun (tek tur veya iki tur kabul).
// - std::sort KULLANMA (sıralama yok).
// - Diziyi değiştirmiyorsun, sadece okuyorsun.
//
// Örnekler:
//
//   arr = [5, 9, 1, 9, 7]
//   → En büyük = 9
//     İkinci en büyük = 7
//     second_largest(...) → 7 döndürmeli
//
//   arr = [4, 4, 4]
//   → Tüm elemanlar aynı, farklı ikinci büyük yok
//     second_largest(...) → -1 döndürmeli
//
//   arr = [1, 2]
//   → En büyük = 2
//     İkinci en büyük = 1
//     second_largest(...) → 1 döndürmeli
//
//   arr = [10]
//   → Tek eleman var, ikinci en büyük yok
//     second_largest(...) → -1 döndürmeli

#include <iostream>
#include <cstddef>
#include <climits>

int second_largest(const int *arr, std::size_t n)
{
    if (n < 2)
    {
        return -1; // ikinci en büyük olamaz
    }

    int max1 = arr[0];        // en büyük
    int max2 = INT_MIN;       // ikinci en büyük (şimdilik çok küçük)
    bool foundSecond = false; // gerçekten ikinci bir farklı değer bulduk mu?

    for (std::size_t i = 1; i < n; ++i)
    {
        int x = arr[i];

        if (x > max1)
        {
            // yeni en büyük bulundu, eski max1 artık ikinci en büyük
            max2 = max1;
            max1 = x;
            foundSecond = true;
        }
        else if (x < max1 && x > max2)
        {
            // max1'den küçük ama şu ana kadarki max2'den büyük bir aday
            max2 = x;
            foundSecond = true;
        }
        // x == max1 ise: hiçbir şey yapmayız, max1 zaten en büyük
    }

    if (!foundSecond)
    {
        // max1'den farklı ikinci bir sayı hiç bulunamadı
        return -1;
    }

    return max2;
}

int main()
{
    int a1[] = {5, 9, 1, 9, 7};
    int a2[] = {4, 4, 4};
    int a3[] = {1, 2};
    int a4[] = {10};

    std::cout << second_largest(a1, 5) << "\n"; // 7
    std::cout << second_largest(a2, 3) << "\n"; // -1
    std::cout << second_largest(a3, 2) << "\n"; // 1
    std::cout << second_largest(a4, 1) << "\n"; // -1

    return 0;
}
