// 🔹 SORU – Bucket Sort (0..1 arası float)
//
// Mantık:
//   - [0,1) aralığını kovalara böl
//   - Her elemanı uygun kovaya at
//   - Her kovayı kendi içinde sıralayıp (örn. insertion sort) birleştir
//
// Fonksiyon imzası:
//     void bucket_sort(float arr[], int n);
//
// Kısıt:
//   - 0.0 <= arr[i] < 1.0
//

#include <vector>

void insertion_sort_float(std::vector<float> &v)
{
    for (int i = 1; i < (int)v.size(); i++)
    {
        float key = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] > key)
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
    }
}

void bucket_sort(float arr[], int n)
{
    // n kova kullanıyoruz
    std::vector<std::vector<float>> buckets(n);

    // Elemanları kovalarına dağıt
    for (int i = 0; i < n; i++)
    {
        int bi = static_cast<int>(arr[i] * n); // kova index'i
        if (bi == n)
            bi = n - 1; // güvenlik
        buckets[bi].push_back(arr[i]);
    }

    // Her kovayı kendi içinde sırala
    for (int i = 0; i < n; i++)
    {
        insertion_sort_float(buckets[i]);
    }

    // Kovaları sırayla geri birleştir
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        for (float x : buckets[i])
        {
            arr[index] = x;
            index++;
        }
    }
}
