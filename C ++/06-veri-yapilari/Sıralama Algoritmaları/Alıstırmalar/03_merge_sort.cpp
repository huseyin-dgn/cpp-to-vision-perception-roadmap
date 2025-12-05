// 🔹 SORU – Merge Sort Algoritmasını Yaz
//
// Merge Sort, "böl ve fethet" (divide & conquer) mantığıyla çalışır:
//
//   1) Diziyi ortadan ikiye böl
//   2) Sol yarıyı rekürsif olarak sırala
//   3) Sağ yarıyı rekürsif olarak sırala
//   4) İki sıralı yarıyı BİRLEŞTİR (merge)
//
// Fonksiyon imzası:
//
//     void merge_sort(int arr[], int left, int right);
//
// Ek olarak, iki sıralı parçayı birleştirmek için:
//
//     void merge(int arr[], int left, int mid, int right);
//
// Örnek:
//
//   int arr[] = {5, 2, 9, 1, 3};
//   merge_sort(arr, 0, 4);
//   // sonuç: 1 2 3 5 9
//
// Kurallar:
//   - Rekürsif çalışacak
//   - merge fonksiyonu, arr[left..mid] ve arr[mid+1..right] sıralı kabul edip
//     bunları tek bir sıralı parça haline getirecek
//   - Ek yardımcı dizi (temporary array) kullanabilirsin
//

void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1; // sol parçanın uzunluğu
    int n2 = right - mid;    // sağ parçanın uzunluğu

    // Geçici diziler
    int *L = new int[n1];
    int *R = new int[n2];

    // Sol parçayı kopyala
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    // Sağ parçayı kopyala
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;    // L için index
    int j = 0;    // R için index
    int k = left; // ana dizi için index

    // İki parçayı birleştir
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Solda kalan elemanlar varsa kopyala
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Sağda kalan elemanlar varsa kopyala
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Geçici dizileri serbest bırak
    delete[] L;
    delete[] R;
}

void merge_sort(int arr[], int left, int right)
{
    if (left >= right)
        return; // Tek elemanlı veya boş aralık → zaten sıralı

    int mid = left + (right - left) / 2;

    // Sol yarıyı sırala
    merge_sort(arr, left, mid);

    // Sağ yarıyı sırala
    merge_sort(arr, mid + 1, right);

    // İki sıralı yarıyı birleştir
    merge(arr, left, mid, right);
}
