// 🔹 SORU – Counting Sort Algoritmasını Yaz
//
// Mantık:
//   - Elemanların frekansını say
//   - Bu sayımla sıralı diziyi yeniden oluştur
//
// Kısıt:
//   - Dizideki elemanlar 0 ile maxValue arasında (negatif yok)
//
// Fonksiyon imzası:
//     void counting_sort(int arr[], int n, int maxValue);
//

void counting_sort(int arr[], int n, int maxValue)
{
    // 0..maxValue arası sayım dizisi
    int *count = new int[maxValue + 1]{0};

    // Frekans sayımı
    for (int i = 0; i < n; i++)
    {
        count[arr[i]]++;
    }

    // count dizisine göre arr'yi yeniden doldur
    int index = 0;
    for (int value = 0; value <= maxValue; value++)
    {
        while (count[value] > 0)
        {
            arr[index] = value;
            index++;
            count[value]--;
        }
    }

    delete[] count;
}
