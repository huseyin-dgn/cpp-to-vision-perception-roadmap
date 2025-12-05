// 🔹 Soru 4 – Belirli Değeri Sil (Tümünü)

// İmza:

// std::size_t remove_value(int* arr, std::size_t n, int x);

// İstenen:

// Diziden x değerine sahip TÜM elemanları çıkar.
// Sağdaki elemanları sola kaydırarak boşlukları doldur.
// Yeni eleman sayısını (yeni n) return et.
// Örnek: arr = [1,3,3,2,3], n=5, x=3
// Son durumda arr ≈ [1,2,?, ?, ?], dönen değer = 2.

#include <iostream>
#include <cstddef>

std::size_t remove_value(int *arr, std::size_t n, int x)
{
    std::size_t write = 0; // yeni dizinin uzunluğu / yazma konumu

    for (std::size_t read = 0; read < n; ++read)
    {
        if (arr[read] != x)
        {
            // Bu elemanı tutmak istiyoruz, sola kaydır (veya aynı yere yaz)
            arr[write] = arr[read];
            ++write;
        }
        // arr[read] == x ise: hiçbir şey yapmıyoruz, yani onu "atmış" oluyoruz
    }

    // write artık yeni eleman sayısı
    return write;
}

int main()
{
    int arr[10] = {1, 3, 3, 2, 3, 4, 3, 5, 3, 6};
    std::size_t n = 10;
    int x = 3;

    std::cout << "Once:  ";
    for (std::size_t i = 0; i < n; ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';

    std::size_t new_n = remove_value(arr, n, x);

    std::cout << "Sonra: ";
    for (std::size_t i = 0; i < new_n; ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << "\nYeni boyut: " << new_n << '\n';

    return 0;
}
