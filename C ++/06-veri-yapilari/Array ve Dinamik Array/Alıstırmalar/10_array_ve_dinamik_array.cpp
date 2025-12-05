// Soru:

// Dinamik bir dizi düşün:
//    int* arr = new int[5] { 1, 2, 3, 4, 5 };
//    size = 5;

// Görev:
//   void rotate_right(int* arr, int size, int k);

// - Diziyi sağa doğru k adım döndür.
// - Örnek: [1,2,3,4,5], k = 2 → [4,5,1,2,3]
// - k büyük olabilir, önce k %= size yap.
// - Ekstra geçici bir dizi (temp) kullanmana İZİN VAR.

#include <iostream>

void rotate_right(int *arr, int size, int k)
{
    if (size <= 1)
    {
        return; // 0 veya 1 elemanlı dizi değişmez
    }

    k = k % size;
    if (k == 0)
    {
        return; // döndürmeye gerek yok
    }

    // Geçici dizi
    int *temp = new int[size];

    // Yeni yerlerine kopyala
    for (int i = 0; i < size; ++i)
    {
        int newIndex = (i + k) % size;
        temp[newIndex] = arr[i];
    }

    // temp'i geri arr'ye yaz
    for (int i = 0; i < size; ++i)
    {
        arr[i] = temp[i];
    }

    delete[] temp;
}

int main()
{
    int size = 5;
    int *arr = new int[size]{1, 2, 3, 4, 5};

    std::cout << "Once:  ";
    for (int i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    int k = 2;
    rotate_right(arr, size, k);

    std::cout << "Sonra: ";
    for (int i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    delete[] arr;
    return 0;
}
