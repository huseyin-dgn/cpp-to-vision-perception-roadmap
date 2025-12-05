// 🔹 SORU – Heap Sort Algoritmasını Yaz
//
// Heap Sort, binary heap (özellikle max-heap) kullanarak çalışan bir sıralama algoritmasıdır.
//
// Mantık:
//   1) Diziden bir MAX-HEAP oluştur (en büyük eleman kökte olur).
//   2) Kökü (en büyük elemanı) dizinin sonuna gönder (swap).
//   3) Heap boyutunu 1 azalt, kalan kısmı tekrar heapify et.
//   4) Bunu dizi tamamen sıralanana kadar tekrar et.
//
// Fonksiyon imzaları:
//
//     void heapify(int arr[], int n, int i);
//     void heap_sort(int arr[], int n);
//
// Açıklama:
//   - heapify: i index'indeki düğümü kökü olduğu alt ağaçta "aşağı doğru" düzelterek
//              max-heap özelliğini sağlar.
//   - heap_sort: önce tüm dizi için max-heap kurar, sonra teker teker kökü sona atar.
//
// Örnek:
//   int arr[] = {5, 2, 9, 1, 3};
//   heap_sort(arr, 5);
//   // sonuç: 1 2 3 5 9
//
// Kurallar:
//   - Binary heap dizide tutuluyor:
//         left child  = 2*i + 1
//         right child = 2*i + 2
//   - heapify fonksiyonu REKÜRSİF olabilir
//

void heapify(int arr[], int n, int i)
{
    int largest = i;       // kök (şimdilik en büyük bu)
    int left = 2 * i + 1;  // sol çocuk
    int right = 2 * i + 2; // sağ çocuk

    // Sol çocuk varsa ve kökten büyükse
    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }

    // Sağ çocuk varsa ve şimdiki en büyükten de büyükse
    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }

    // En büyük eleman kök değilse, yer değiştir ve alt ağacı düzelt
    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Alt ağaç için heapify
        heapify(arr, n, largest);
    }
}

void heap_sort(int arr[], int n)
{
    // 1) Max-heap oluştur (diziyi heap'e çevir)
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    // 2) En büyük elemanı (kök) sona at, heap'i küçült, tekrar heapify et
    for (int i = n - 1; i > 0; i--)
    {
        // Kök (en büyük) ile son elemanı swap et
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Azalan heap boyutuyla kökten itibaren heapify
        heapify(arr, i, 0);
    }
}
