// Aşağıdaki fonksiyonu tamamlayarak Bubble Sort algoritmasını gerçekleştir.
//
// Görev:
//   - Yan yana duran iki elemanı karşılaştır
//   - Eğer soldaki > sağdaki ise yer değiştir (swap)
//   - Bu işlemi dizi tamamen sıralanana kadar tekrarla
//
// Fonksiyon imzası:
//
//     void bubble_sort(int arr[], int n);
//
// Kurallar:
//   - std::swap YOK → kendi swap işlemini elle yaz
//   - İç içe 2 for döngüsü kullan
//   - Her dış döngü turunda en büyük eleman sona “yüzer”
//
// Örnek:
//   int arr[] = {5, 2, 9, 1, 3};
//   bubble_sort(arr, 5);
//   // sonuç: 1 2 3 5 9

#include <iostream>
#include <cstddef>

void bubble_sort(int arr[], int n)
{
    for (std::size_t i = 0; i < n - 1; i++)
    {
        for (std::size_t a = 0; a < n - 1; a++)
        {
            if (arr[a] > arr[a + 1])
            {
                int temp = arr[a];
                arr[a] = arr[a + 1];
                arr[a + 1] = temp;
            }
        }
    }
}
