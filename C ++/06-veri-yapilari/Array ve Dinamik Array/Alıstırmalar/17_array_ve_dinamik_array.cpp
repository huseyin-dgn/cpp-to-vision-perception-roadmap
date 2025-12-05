// 🔹 Soru – İki Sayının Toplamı (Two Sum) – O(n) Çözüm
//
// İmza:
//
//     int find_two_sum(const int* arr, std::size_t n, int target);
//
// Tanım:
//   Bir dizide iki farklı eleman seç,
//   toplamları "target" değerine eşit olsun.
//
// Görev:
//   - Eğer böyle bir çift varsa 1 döndür
//   - Yoksa 0 döndür
//
// Örnek:
//
//   arr = [2, 7, 11, 15], target = 9
//   → 2 + 7 = 9 → sonuç = 1
//
//   arr = [3, 8, 4, 1], target = 100
//   → hiçbir çift 100 yapmaz → sonuç = 0
//
//
// İstenen:
//
//   ✔ Çözüm 1: Bruteforce O(n²) (istedin yaz ama gerek yok)
//   ✔ Çözüm 2: Hash Table ile O(n) çöz
//
//   Bu sorunun profesyonel çözümü O(n) hash tablosu ile:
//
//     - Bir hash set düşün (unordered_set).
//     - Dizi boyunca ilerle:
//         "aradığım değer" = target - arr[i]
//         eğer bu değer hash içinde varsa → çift bulundu
//         yoksa arr[i]'yi hash'e ekle
//
//   Tek geçiş → O(n)
//
// Kurallar:
//
//   - Diziyi değiştirme.
//   - Ekstra dizi yok, sadece hash set (O(1) amortized).
//   - Bulur bulmaz 1 döndür.
//   - Bulamazsan döngü bitince 0 döndür.
//
// Ek Örnek:
//
//   arr = [1, 3, 5, 8], target = 9
//   → 1 + 8 = 9  → sonuç = 1
//
//   arr = [1, 2, 3, 4], target = 50
//   → sonuç = 0

#include <iostream>
#include <cstddef>
#include <unordered_set>

int find_two_sum(const int *arr, std::size_t n, int target)
{
    if (n < 2)
        return 0;

    std::unordered_set<int> seen;

    for (std::size_t i = 0; i < n; ++i)
    {
        int x = arr[i];
        int need = target - x;

        if (seen.count(need))
        {
            return 1; // çift bulundu
        }

        seen.insert(x); // bu sayıyı artık gördük
    }

    return 0; // hiç çift bulunamadı
}
