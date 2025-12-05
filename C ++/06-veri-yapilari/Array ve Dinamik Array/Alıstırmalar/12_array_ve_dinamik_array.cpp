// 🔹 SORU: Dinamik Dizide Index'ten Eleman Sil (erase_at)
//
// Elinde şöyle bir dinamik dizi var:
//
//   int* arr = new int[7] { 10, 20, 99, 30, 40, 50, 60 };
//
//   int size = 7;
//   int capacity = 7;
//
// Görev:
//   Verilen index'teki elemanı SİL,
//   sağdaki elemanları sola kaydır,
//   size'ı 1 azalt.
//
// Fonksiyon imzası:
//
//   void erase_at(int* arr, int& size, int index);
//
// Kurallar:
//
// 1) Eğer index < 0 veya index >= size ise:
//        Geçersiz index → hiçbir şey yapma (return).
//
// 2) Silme işlemi:
//        index'ten sonraki elemanları sola kaydır:
//            for (i = index; i < size - 1; ++i)
//                arr[i] = arr[i + 1];
//
// 3) Döngü bittikten sonra:
//        size--;   // eleman sayısını 1 azalt
//
// Örnek:
//
//   Başlangıç:
//       arr = [10, 20, 99, 30, 40, 50, 60]
//       size = 7
//
//   erase_at(arr, size, 2);   // index = 2'deki 99'u sil
//
//   Sonuç:
//       arr = [10, 20, 30, 40, 50, 60, ?]
//       size = 6
//   (son elemanın ne olduğunun önemi yok, size artık 6)
//
// NOT:
//   - Yeni dizi oluşturmak yok.
//   - capacity değişmiyor, sadece size değişiyor.
//   - Silme = sağdakileri sola çekme.

#include <iostream>

void erase_at(int *arr, int &size, int index)
{
    // 1) Geçersiz index kontrolü
    if (index < 0 || index >= size)
    {
        return; // hiçbir şey yapma
    }

    // 2) Sağdakileri sola kaydır
    for (int i = index; i < size - 1; ++i)
    {
        arr[i] = arr[i + 1];
    }

    // 3) Eleman sayısını 1 azalt
    --size;
}

int main()
{
    int capacity = 7;
    int *arr = new int[capacity]{10, 20, 99, 30, 40, 50, 60};
    int size = 7;

    std::cout << "Once:  ";
    for (int i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    // index = 2'deki 99'u silelim
    erase_at(arr, size, 2);

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

// Eğer silme işlemi yapmak istiyorsan diziyi soldan sağa incelemen gerekiyor.Silerken boşluğu solda kapatıyorsun.Sağdakiler sola çekiliyor.
// Ama ekleme işleminde işler tam tersi.Bu sefer sağdan sola gitmen lazım.Çünkü eklerken boşluk açıyorsun.Soldakiler sağa itiliyor.