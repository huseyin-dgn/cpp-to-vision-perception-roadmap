// 🔹 Soru – Vector uzerinde ekleme, silme ve guncelleme islemleri
//
// Görev:
//
//  1) Kullanıcıdan n al (pozitif).
//  2) n tane tamsayi oku ve vector<int> v içine push_back ile ekle.
//  3) Asagidakileri sirayla yap:
//
//     a) Ilk hali:
//        - "Ilk vector:" basligi ile tum elemanlari yazdir.
//
//     b) Sona eleman ekle (push_back):
//        - Kullanıcıdan bir tamsayi daha al (yeniDeger).
//        - v.push_back(yeniDeger) ile vector'un SONUNA ekle.
//        - "Sona ekleme sonrasi:" diye yazdir.
//
//     c) Sondan eleman sil (pop_back):
//        - v.pop_back() cagir.
//        - "Sondan silme (pop_back) sonrasi:" diye yazdir.
//        - Dikkat: pop_back, son elemani siler, geriye deger DONDURMEZ.
//
//     d) Belli index'e eleman ekle (insert):
//        - Kullanıcıdan bir index (idx) ve bir deger (val) iste.
//        - Eger 0 <= idx <= v.size() ise:
//              v.insert( v.begin() + idx, val );
//          yoksa "Gecersiz index" de ve bu adimi atla.
//        - "Araya ekleme (insert) sonrasi:" yazdir.
//
//     e) Belli index'teki elemani sil (erase):
//        - Kullanıcıdan bir index daha iste (delIdx).
//        - Eger 0 <= delIdx < v.size() ise:
//              v.erase( v.begin() + delIdx );
//          yoksa "Gecersiz index" de.
//        - "Index'e gore silme (erase) sonrasi:" yazdir.
//
//     f) front() ve back():
//        - Eger vector bos degilse:
//              v.front() ve v.back() degerlerini yaz.
//
//     g) Tum vector'u temizle (clear):
//        - v.clear() cagir.
//        - vector'un bos olup olmadigini v.empty() ile kontrol edip yaz.
//
// Amaç:
//  - push_back / pop_back / insert / erase / clear / front / back / empty
//    gibi temel vector fonksiyonlarini GERÇEK senaryo icinde gormek.

#include <iostream>
#include <vector>

int main()
{
    int n;
    std::cout << "Kac eleman gireceksin? ";
    std::cin >> n;

    if (n < 0)
    {
        std::cout << "Negatif n olmaz.\n";
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

    // a) Ilk vector
    std::cout << "\n[1] Ilk vector: ";
    for (auto x : v)
    {
        std::cout << x << " ";
    }
    std::cout << "\n";

    // b) Sona eleman ekle (push_back)
    int yeniDeger;
    std::cout << "\nSona eklenecek sayiyi gir: ";
    std::cin >> yeniDeger;
    v.push_back(yeniDeger);

    std::cout << "[2] Sona ekleme (push_back) sonrasi: ";
    for (auto x : v)
    {
        std::cout << x << " ";
    }
    std::cout << "\n";

    // c) Sondan eleman sil (pop_back)
    if (!v.empty())
    {                 // bos degilse
        v.pop_back(); // son elemani sil
    }

    std::cout << "[3] Sondan silme (pop_back) sonrasi: ";
    for (auto x : v)
    {
        std::cout << x << " ";
    }
    std::cout << "\n";

    // d) Belli index'e eleman ekle (insert)
    int idx, val;
    std::cout << "\nAraya eklemek icin index ve deger gir (idx val): ";
    std::cin >> idx >> val;

    if (idx >= 0 && idx <= static_cast<int>(v.size()))
    {
        // v.begin() + idx, v'deki idx. konuma isaret eden iterator
        v.insert(v.begin() + idx, val);
        std::cout << "[4] Araya ekleme (insert) sonrasi: ";
        for (auto x : v)
        {
            std::cout << x << " ";
        }
        std::cout << "\n";
    }
    else
    {
        std::cout << "Gecersiz index, araya ekleme yapilmadi.\n";
    }

    // e) Belli index'teki elemani sil (erase)
    int delIdx;
    std::cout << "\nSilinecek elemanin index'ini gir (delIdx): ";
    std::cin >> delIdx;

    if (delIdx >= 0 && delIdx < static_cast<int>(v.size()))
    {
        v.erase(v.begin() + delIdx);
        std::cout << "[5] Index'e gore silme (erase) sonrasi: ";
        for (auto x : v)
        {
            std::cout << x << " ";
        }
        std::cout << "\n";
    }
    else
    {
        std::cout << "Gecersiz index, silme yapilmadi.\n";
    }

    // f) front() ve back()
    if (!v.empty())
    {
        std::cout << "\n[6] front() ve back():\n";
        std::cout << "Ilk eleman (front): " << v.front() << "\n";
        std::cout << "Son eleman (back):  " << v.back() << "\n";
    }
    else
    {
        std::cout << "\nVector bos, front/back yok.\n";
    }

    // g) Tum vector'u temizle (clear)
    v.clear();

    std::cout << "\n[7] clear() sonrasi: ";
    if (v.empty())
    {
        std::cout << "Vector bos (empty() = true)\n";
    }
    else
    {
        std::cout << "Hala eleman var (empty() = false)\n";
    }

    return 0;
}
