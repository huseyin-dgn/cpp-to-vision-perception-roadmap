// 🔹 Soru 1 – String uzunluğu + karakterleri yazdırma
//
// int string_length(const std::string& s);
//
// İstenen:
//  - Kullanıcıdan bir kelime al (boşluksuz).
//  - string_length fonksiyonu, bu kelimenin uzunluğunu döndürsün.
//  - Fonksiyon içinde:
//      * s.size() kullan
//      * static_cast<int>(s.size()) kullan
//      * for (auto c : s) ile karakterleri sırayla yazdır (yan yana)
//  - main içinde:
//      * Kullanıcıdan kelimeyi al
//      * string_length(s) çağır
//      * Uzunluğu ekrana yazdır
//
// Bu soruda özellikle görmek istediklerimiz:
//  - std::string
//  - s.size()
//  - static_cast<int>(...)
//  - range-based for: for (auto c : s) { ... }

#include <iostream>
#include <string>

int string_length(const std::string &s)
{
    // s.size() -> std::size_t (işaretsiz tip)
    //      s.size() → stringin kaç karakter olduğunu verir.

    //      static_cast<int> → sayıyı int’e çevirir.

    //      len → sadece bir sayı, örneğin: 6.

    int len = static_cast<int>(s.size());

    std::cout << "Karakterler : ";

    // for (auto c : s) -> s içindeki her karakteri sırayla gezer
    for (auto c : s)
    {
        std::cout << c << ' ';
    }
    std::cout << "\n";

    return len;
}

int main()
{
    std::string kelime;

    std::cout << "Bir kelime girin : ";

    std::cin >> kelime; // bosluk gorunce durur

    int len = string_length(kelime);
    std::cout << "Kelime uzunlugu :";

    return 0;
}

// -- BU SORUNUN DETAYLARINI - acıklamalar.ipynb - DOSYASINDA BULABİLİRSİNİZ.