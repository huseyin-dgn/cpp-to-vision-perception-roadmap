// 🔹 Soru 5 – İki Sıralı Diziyi Birleştir
//
// void merge_sorted_arrays(const int* a, std::size_t n,
//                          const int* b, std::size_t m,
//                          int* out);
//
// a ve b: artan sıralı iki dizi
// out: boyutu n + m olan çıktı dizisi
// Amaç: a ve b'yi birleştirip out içine artan sıralı şekilde yazmak.

#include <iostream>
#include <cstddef>

void merge_sorted_arrays(const int *a, std::size_t n,
                         const int *b, std::size_t m,
                         int *out)
{
    std::size_t i = 0; // a dizisi icin index
    std::size_t j = 0; // b dizisi icin index
    std::size_t k = 0; // out dizisi icin index

    // Her iki dizide de eleman varken
    while (i < n && j < m)
    {
        if (a[i] <= b[j])
        {
            out[k] = a[i];
            ++i;
        }
        else
        {
            out[k] = b[j];
            ++j;
        }
        ++k;
    }

    // a'nın kalan elemanları
    while (i < n)
    {
        out[k] = a[i];
        ++i;
        ++k;
    }

    // b'nin kalan elemanları
    while (j < m)
    {
        out[k] = b[j];
        ++j;
        ++k;
    }
}

int main()
{
    int a[5] = {1, 3, 5, 7, 9};
    int b[4] = {2, 4, 6, 8};

    std::size_t n = 5;
    std::size_t m = 4;

    int out[9];

    merge_sorted_arrays(a, n, b, m, out);

    std::cout << "Birlesik dizi: ";
    for (std::size_t i = 0; i < n + m; ++i)
    {
        std::cout << out[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}
