// 🔹 Soru – Vector'de belirli bir aralığı ters çevir ve araya eleman ekle
//
// 1) Kullanıcıdan n al.
// 2) n tane sayı oku ve vector<int> v içine push_back ile ekle.
// 3) Kullanıcıdan iki sayı al: L ve R
//      Şart: 0 <= L < R <= v.size()
//      Görev: v[L...R-1] aralığını TERS ÇEVİR.
//
//         Örnek:
//            v = [10, 20, 30, 40, 50]
//            L = 1, R = 4
//            ters cevrilecek bolge: 20, 30, 40
//            sonuç: [10, 40, 30, 20, 50]
//
//      Yani:
//           std::reverse( v.begin() + L, v.begin() + R );
//
// 4) Kullanıcıdan bir index (idx) ve bir değer (val) al:
//        v.insert( v.begin() + idx, val )
//
// 5) Kullanıcıdan bir index (delIdx) al:
//        v.erase( v.begin() + delIdx );
//
// 6) Son halini sort ile sırala ve yazdır.
//
// Bu soruda amaç: begin,end, begin()+i, reverse, insert, erase, sort hepsini
// TEK bir pratik içinde oturtmaktır.

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int n;
    std::cout << "Kac eleman gireceksin? ";
    std::cin >> n;

    std::vector<int> v;
    v.reserve(n);

    std::cout << n << " adet sayi gir:\n";
    for (int i = 0; i < n; i++)
    {
        int x;
        std::cin >> x;
        v.push_back(x);
    }

    // --- 3) Araligi ters cevir ---
    int L, R;
    std::cout << "Ters cevrilecek aralik icin L ve R gir (L < R): ";
    std::cin >> L >> R;

    if (L >= 0 && R <= static_cast<int>(v.size()) && L < R)
    {
        std::reverse(v.begin() + L, v.begin() + R);
    }
    else
    {
        std::cout << "Gecersiz aralik, ters cevirme atlandi.\n";
    }

    std::cout << "Ters cevrilmis vector: ";
    for (auto x : v)
        std::cout << x << " ";
    std::cout << "\n";

    // --- 4) Araya eleman ekle (insert) ---
    int idx, val;
    std::cout << "Araya eklemek icin index ve deger gir (idx val): ";
    std::cin >> idx >> val;

    if (idx >= 0 && idx <= static_cast<int>(v.size()))
    {
        v.insert(v.begin() + idx, val);
    }
    else
    {
        std::cout << "Gecersiz idx, ekleme yapilmadi.\n";
    }

    std::cout << "Araya ekleme sonrasi: ";
    for (auto x : v)
        std::cout << x << " ";
    std::cout << "\n";

    // --- 5) Eleman sil (erase) ---
    int delIdx;
    std::cout << "Silinecek index'i gir: ";
    std::cin >> delIdx;

    if (delIdx >= 0 && delIdx < static_cast<int>(v.size()))
    {
        v.erase(v.begin() + delIdx);
    }
    else
    {
        std::cout << "Gecersiz delIdx, silme yapilmadi.\n";
    }

    std::cout << "Silme sonrasi: ";
    for (auto x : v)
        std::cout << x << " ";
    std::cout << "\n";

    // --- 6) Sirala ---
    std::sort(v.begin(), v.end());

    std::cout << "Siralanmis son vector: ";
    for (auto x : v)
        std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
