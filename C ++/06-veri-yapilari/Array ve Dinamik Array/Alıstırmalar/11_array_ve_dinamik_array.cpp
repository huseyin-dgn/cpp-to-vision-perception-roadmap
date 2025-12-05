// 🔹 SORU: Dinamik Dizide Araya Eleman Ekle (insert)
//
// Elinizde şöyle bir dinamik dizi var:
//
// int* arr = new int[6] { 10, 20, 30, 40, 50, 60 };
//
// size = 6
// capacity = 6
//
// Görev:
//   "index" konumuna "value" değerini EKLE.
//
//   Fonksiyon imzası şöyle olsun:
//
//   void insert_at(int* arr, int& size, int capacity,
//                  int index, int value);
//
// Kurallar:
//
// 1) Eğer size == capacity ise:
//        bu soruda kapasite artırma YAPMA
//        (yani index kapasiteyi aşarsa işlem yapılmasın)
//
// 2) Eğer index > size ise:
//        işlem yapma (geçersiz index)
//
// 3) Kaydırma:
//        index'ten başlayarak sağa doğru kaydır:
//            arr[i+1] = arr[i]
//        bunu i = size-1'den index'e doğru yap
//
// 4) Sonra arr[index] = value
//
// 5) size++
//
// Örnek:
//
// arr = [10, 20, 30, 40, 50, 60]
// insert_at(..., index = 2, value = 99)
//
// sonuç:
//       [10, 20, 99, 30, 40, 50, 60]
// size = 7
//
// NOT: kapasite artırma YOK, sadece kaydırma.
// NOT: yeni dizi oluşturmak YOK, sadece mevcut buffer üzerinde çalış.
//```

#include <iostream>

void insert_at(int *arr, int &size, int capacity,
               int index, int value)
{
    // 1) Yer yoksa hiçbir şey yapma
    if (size == capacity)
    {
        return;
    }

    // 2) Index geçersizse hiçbir şey yapma
    if (index > size || index < 0)
    {
        return;
    }

    // 3) Sondan başlayarak sağa kaydır
    //    i: size - 1, size - 2, ..., index
    for (int i = size - 1; i >= index; --i)
    {
        arr[i + 1] = arr[i];
    }

    // 4) Boşalan index'e yeni değeri yaz
    arr[index] = value;

    // 5) Eleman sayısını artır
    ++size;
}

int main()
{
    int capacity = 7;
    int *arr = new int[capacity]{10, 20, 30, 40, 50, 60, 0};

    int size = 6;

    std::cout << "Once:  ";
    for (int i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    insert_at(arr, size, capacity, 2, 99);

    std::cout << "Sonra: ";
    for (int i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    std::cout << "size = " << size << "\n";
    std::cout << "capacity = " << capacity << "\n";

    delete[] arr;
    return 0;
}
