// 🔹 SORU – Insertion Sort Algoritmasını Yaz
//
// Mantık:
//   - Diziyi soldan sağa dolaş
//   - arr[i] değerini al (bu "key" olacak)
//   - Soldaki sıralı bölümde key’den büyük elemanları sağa kaydır
//   - Key’i doğru boşluğa yerleştir
//
// Fonksiyon imzası:
//      void insertion_sort(int arr[], int n);
//
// Örnek:
//   int arr[] = {5, 2, 9, 1, 3};
//   insertion_sort(arr, 5);
//   // sonuç: 1 2 3 5 9
//
// Kurallar:
//   - İçeride while döngüsü olacak
//   - Elemanları sağa kaydırmayı unutma
//   - swap yok, kaydırarak ilerliyorsun
//   - i = 1’den başla çünkü arr[0] zaten “tek başına sıralı”
//

void insertion_sort(int arr[], int n)
{
    for (int i = 1; i < n; i++) // i = 1'den başlıyoruz
    {
        int key = arr[i]; // Yerine yerleştirilecek eleman
        int j = i - 1;    // Soldaki sıralı kısmın son elemanı

        // Solda key'den büyük olanları sağa kaydırıyoruz
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j]; // Elemanı sağa kaydır
            j--;                 // Bir sola ilerle
        }

        // Key'i açılan boşluğa yerleştiriyoruz
        arr[j + 1] = key;
    }
}
