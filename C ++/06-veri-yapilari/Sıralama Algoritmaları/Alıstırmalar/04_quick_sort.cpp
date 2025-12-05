// 🔹 SORU – Quick Sort Algoritmasını Yaz
//
// Quick Sort, "böl ve fethet" (divide & conquer) mantığıyla çalışan bir sıralama algoritmasıdır.
//
// Mantık (Lomuto partition yöntemiyle):
//   1) Bir pivot seç (genelde son eleman).
//   2) Diziyi pivot'tan küçükler ve büyükler olarak iki bölgeye ayır (partition).
//   3) Pivot'un solundaki kısmı rekürsif sırala.
//   4) Pivot'un sağındaki kısmı rekürsif sırala.
//
// Fonksiyon imzaları:
//
//     int partition(int arr[], int low, int high);
//     void quick_sort(int arr[], int low, int high);
//
// Örnek:
//
//   int arr[] = {5, 2, 9, 1, 3};
//   quick_sort(arr, 0, 4);
//   // sonuç: 1 2 3 5 9
//
// Kurallar:
//   - partition fonksiyonu, pivot'u doğru yerine yerleştirmeli
//   - quick_sort, partition’dan dönen pivot index'ine göre
//     sol ve sağ kısımları rekürsif çağırmalı
//   - Ekstra büyük yardımcı dizi kullanma (in-place çalışsın)
//

int partition(int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot = son eleman
    int i = low - 1;       // küçük elemanların son index'i

    for (int j = low; j < high; j++)
    {
        // Eğer arr[j] pivot'tan küçük veya eşitse
        if (arr[j] <= pivot)
        {
            i++;
            // arr[i] ile arr[j]'yi yer değiştir
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Pivot'u doğru konuma al: i+1 ile high'i swap et
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1; // pivot'un doğru index'i
}

void quick_sort(int arr[], int low, int high)
{
    if (low >= high)
        return; // Tek eleman veya boş aralık → zaten sıralı

    int pivotIndex = partition(arr, low, high);

    // Pivot'un solunu sırala
    quick_sort(arr, low, pivotIndex - 1);

    // Pivot'un sağını sırala
    quick_sort(arr, pivotIndex + 1, high);
}
