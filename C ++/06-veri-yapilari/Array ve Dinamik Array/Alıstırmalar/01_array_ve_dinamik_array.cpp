// 🔹 Soru 1 – Eleman Sayma

// İmza:

// int count_occurrences(const int* arr, std::size_t n, int x);

// İstenen:

// arr dizisinde, x değerinin kaç kere geçtiğini bul ve döndür.

#include <iostream>
#include <cstddef>

int count_occurrences(const int *arr, std::size_t n, int x)
{
    int count = 0;

    for (std::size_t i = 0; i < n; ++i)
    {
        if (arr[i] == x)
        {
            ++count;
        }
    }

    return count;
}

int main()
{
    int arr[7] = {1, 3, 3, 5, 3, 7, 3};
    std::size_t n = 7;

    int x = 3;
    int result = count_occurrences(arr, n, x);

    std::cout << x << " sayisi dizide " << result << " kez geciyor.\n";

    return 0;
}
