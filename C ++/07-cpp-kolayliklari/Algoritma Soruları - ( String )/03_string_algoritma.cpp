// 🔹 Soru 4 – Sadece harfleri BÜYÜK yap, diğer karakterlere dokunma
//
// std::string uppercase_letters_only(std::string s);
//
// İstenen:
//  - Kullanıcıdan boşluk içerebilen bir cümle al (std::getline ile).
//  - uppercase_letters_only fonksiyonu:
//      * s içindeki sadece ALFABETİK karakterleri (a-z, A-Z) büyük harfe çevirsin.
//      * Rakam, boşluk, noktalama vs. olduğu gibi kalsın.
//      * Kaç tane harfin değiştirildiğini ekrana yazdırabilir (opsiyonel).
//      * Değiştirilmiş string'i return etsin.
//  - main içinde:
//      * Cümleyi al
//      * Fonksiyonu çağır
//      * Sonucu ekrana yaz.
//
// Kullanılacaklar (zorunlu):
//  - std::string
//  - std::getline(std::cin, s)
//  - s.size() + static_cast<int>(...)
//  - range-based for: for (auto& c : s) { ... }
//  - std::isalpha(...)
//  - std::toupper(...)
//  - isalpha / toupper çağrılarında unsigned char cast kullanımı

#include <iostream>
#include <string>
#include <cctype> // std::isalpha, std::toupper

// Sadece harfleri büyük yapan fonksiyon
std::string uppercase_letters_only(std::string s)
{
    int len = static_cast<int>(s.size());
    std::cout << "Cumlenin uzunlugu: " << len << "\n";

    int changed = 0; // kac harf dönüştürdük

    for (auto &c : s)
    {
        // c'yi önce unsigned char'a çeviriyoruz
        unsigned char uc = static_cast<unsigned char>(c);

        // sadece alfabetik karakterse işleme sok
        if (std::isalpha(uc))
        {
            // toupper da unsigned char bekliyor, sonra char'a dönüyoruz
            c = static_cast<char>(std::toupper(uc));
            changed++;
        }
        // rakam, bosluk, noktalama vs. ise hicbir sey yapma
    }

    std::cout << "Buyuk harfe cevrilen harf sayisi: " << changed << "\n";

    return s;
}

int main()
{
    std::string line;

    std::cout << "Bir cumle gir: ";
    std::getline(std::cin, line);

    std::string result = uppercase_letters_only(line);

    std::cout << "Sonuc: " << result << "\n";

    return 0;
}
