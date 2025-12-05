// 🔹 Soru 6  – İlk Geçtiği İndexi Bul

// İmza:
//
// int find_first_index(const int* arr, std::size_t n, int x);
//
// İstenen:
//
// - arr dizisinde x değerini BAŞTAN SONA tara.
// - x ilk nerede bulunuyorsa, o index'i döndür.
// - Eğer x hiç yoksa, -1 döndür.
//
// Örnek:
//   arr = [4, 7, 9, 7, 3], x = 7  → sonuç = 1
//   arr = [1, 2, 3], x = 5        → sonuç = -1

#include <iostream>
#include <cstddef>

int find_first_index(const int *arr, std::size_t n, int x)
{
    for (std::size_t i = 0; i < n; ++i)
    {
        if (arr[i] == x)
        {
            return static_cast<int>(i); // index'i döndürüyoruz
        }
    }

    // Hiç bulunamadıysa:
    return -1;
}

int main()
{
    int arr[5] = {4, 7, 9, 7, 3};
    std::size_t n = 5;

    int idx1 = find_first_index(arr, n, 7);
    int idx2 = find_first_index(arr, n, 3);
    int idx3 = find_first_index(arr, n, 10);

    std::cout << "7 ilk olarak index: " << idx1 << '\n';  // 1
    std::cout << "3 ilk olarak index: " << idx2 << '\n';  // 4
    std::cout << "10 ilk olarak index: " << idx3 << '\n'; // -1

    return 0;
}

// static_cast<T>(expr) → “Bunu T’ye derleme zamanında, normal bir dönüşüm olarak çevir.”

// Biz index döndürürken sadece size_t → int dönüşümü yaptık.
