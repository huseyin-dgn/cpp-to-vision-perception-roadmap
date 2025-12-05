// 🔹 Soru  – Diziyi Tersten Yaz (in-place)
//
// int reverse_array(int* arr, std::size_t n);
//
// - 0 ve n-1, 1 ve n-2, 2 ve n-3 ... yer değiştir
// - Ekstra dizi kullanma
// - Diziyi tamamen ters çevir

#include <iostream>
#include <cstddef>

int reverse_array(int *arr, std::size_t n)
{
    if (n == 0)
    {
        return -1;
    }

    std::size_t left = 0;
    std::size_t right = n - 1;

    while (left < right)
    {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;

        left++;
        right--;
    }

    return 0;
}
int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    reverse_array(arr, 5);

    for (int i = 0; i < 5; ++i)
    {
        std::cout << arr[i] << " ";
    }
}
