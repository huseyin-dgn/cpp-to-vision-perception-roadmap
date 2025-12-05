// 🔹 Soru 3 – Tekleri Başa Topla

// İmza:

// void move_odds_to_front(int* arr, std::size_t n);

// İstenen:

// Dizideki tek sayıları baş tarafa, çift sayıları sona topla.
// Bunu ekstra dizi kullanmadan (in-place) yap.
// Tek ve çiftlerin kendi iç sırası önemli değil.

#include <iostream>
#include <cstddef>

void move_odds_to_front(int *arr, std::size_t n)
{
    std::size_t nextOdd = 0;

    for (std::size_t i = 0; i < n; i++)
    {
        if (arr[i] % 2 != 0)
        {
            int tmp = arr[i];
            arr[i] = arr[nextOdd];
            arr[nextOdd] = tmp;

            ++nextOdd;
        }
    }
}

int main()
{
    int arr[7] = {2, 5, 8, 3, 7, 4, 1};
    std::size_t n = 7;
    std::cout << "Önce : ";

    for (std::size_t i = 0; i < n; i++)
    {
        std::cout << arr[i] << ' ';
    }

    std::cout << "\n";

    move_odds_to_front(arr, n);

    std::cout << "Sonra :";
    for (std::size_t i = 0; i < n; i++)
    {
        std::cout << arr[i] << ' ';
    }

    std::cout << "\n";

    return 0;
}