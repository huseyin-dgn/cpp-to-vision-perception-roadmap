// 🔹 Soru 2 – Dizi Artan Sıralı mı?
//
// İmza:
//
// bool is_sorted_non_decreasing(const int* arr, std::size_t n);
//
// İstenen:

// Dizi artan veya eşit sıralı mı kontrol et.
// Yani her i için: arr[i] <= arr[i+1] olmalı.
// Sağlanıyorsa true, bozuluyorsa false döndür.

#include <iostream>
#include <cstddef>

bool is_sorted_non_decreasing(const int *arr, std::size_t n)
{
    if (n <= 1)
    {
        return true;
    }

    for (std::size_t i = 0; i + 1 < n; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int a1[5] = {1, 2, 2, 5, 9};
    int a2[5] = {1, 3, 0, 4, 8};

    std::cout << "a1 sirali mi? " << (is_sorted_non_decreasing(a1, 5) ? "Evet" : "Hayir") << '\n';
    std::cout << "a2 sirali mi? " << (is_sorted_non_decreasing(a2, 5) ? "Evet" : "Hayir") << '\n';

    return 0;
}

// 🧠 Mantık

// Eğer arr[i] > arr[i+1] herhangi bir yerde doğruysa → dizi sıralı değildir.

// Tüm dizi boyunca kontrol edip bozukluk yoksa → sıralıdır.

// Karmaşıklık:

// Dizi 1 kez taranıyor → O(n)