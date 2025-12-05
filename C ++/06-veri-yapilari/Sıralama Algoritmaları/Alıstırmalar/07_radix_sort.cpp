// 🔹 SORU – Radix Sort (10'luk taban, pozitif int)
//
// Mantık:
//   - Sayıları basamak basamak sıralarsın
//   - Her basamakta (1'ler, 10'lar, 100'ler...) stable bir Counting Sort uygula
//
// Fonksiyon imzası:
//     void radix_sort(int arr[], int n);
//
// Kısıt:
//   - Elemanlar >= 0 (pozitif veya 0)
//
// Yardımcı: belli bir basamağa göre Counting Sort
//

int get_max(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void counting_sort_exp(int arr[], int n, int exp)
{
    int *output = new int[n];
    int count[10] = {0};

    // Bu basamaktaki sayımları yap (exp: 1,10,100,...)
    for (int i = 0; i < n; i++)
    {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    // Kümülâtif sayım (stable sıralama için)
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Tersten giderek output'a yerleştir (stable)
    for (int i = n - 1; i >= 0; i--)
    {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Sonucu arr'ye kopyala
    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    delete[] output;
}

void radix_sort(int arr[], int n)
{
    int mx = get_max(arr, n);

    // 1'ler, 10'lar, 100'ler ... basamakları için Counting Sort
    for (int exp = 1; mx / exp > 0; exp *= 10)
    {
        counting_sort_exp(arr, n, exp);
    }
}
