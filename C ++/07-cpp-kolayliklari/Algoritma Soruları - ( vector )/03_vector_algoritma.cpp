// 🔹 Soru – Vector elemanlarini index ile gez, yazdir ve guncelle
//
// Görev:
//  1) Kullanıcıdan n al (kaç eleman gireceğini).
//  2) n tane tamsayı oku ve std::vector<int> v içine push_back ile ekle.
//  3) Sonra:
//      - a) KLASIK for ile (i = 0..size-1) vectorü dolaş,
//           her elemanın:
//              * index'ini
//              * değerini
//           ekrana yazdır.
//           (Burada v[i] kullanacağız.)
//      - b) İKİNCİ bir adımda, tüm elemanları 10 arttır:
//              v[i] = v[i] + 10;
//           ve güncellenmiş vectorü ekrana yaz.
//      - c) Bu sefer range-based for ile (for (auto x : v))
//           elemanları sadece okuyup ekrana yaz.
//
// Amaç:
//  - v.size() kullanmayı görmek
//  - v[i] ile index üzerinden erişmek
//  - klasik for ile "index tabanlı gezinme"yi öğrenmek
//  - range-based for ile "değer tabanlı gezinme"yi görmek

#include <iostream>
#include <vector>

int main()
{
    int n;
    std::cout << "Kac eleman gireceksin? ";
    std::cin >> n;

    if (n <= 0)
    {
        std::cout << "Pozitif bir n girmen lazim.\n";
        return 1;
    }

    std::vector<int> v;

    std::cout << n << " adet tamsayi gir:\n";
    for (int i = 0; i < n; i++)
    {
        int x;
        std::cin >> x;
        v.push_back(x);
    }

    // --- a) Klasik for + index ile yazdirma ---

    std::cout << "\n[1] Index ile erisim (klasik for):\n";
    for (int i = 0; i < static_cast<int>(v.size()); i++)
    {
        // v[i] → i. indexteki eleman
        std::cout << "index " << i << " -> deger " << v[i] << "\n";
    }

    // --- b) Her elemani 10 arttir (yine index kullanarak) ---

    for (int i = 0; i < static_cast<int>(v.size()); i++)
    {
        v[i] = v[i] + 10; // elemani guncelliyoruz
        // alternatif: v[i] += 10;
    }

    std::cout << "\n[2] Guncellenmis vector (her eleman +10):\n";
    for (int i = 0; i < static_cast<int>(v.size()); i++)
    {
        std::cout << "index " << i << " -> deger " << v[i] << "\n";
    }

    // --- c) Range-based for ile sadece degerleri yazdirma ---

    std::cout << "\n[3] Range-based for (sadece degerler):\n";
    for (auto x : v)
    { // burada x, v icindeki her elemanin KOPYASI
        std::cout << x << " ";
    }
    std::cout << "\n";

    return 0;
}
