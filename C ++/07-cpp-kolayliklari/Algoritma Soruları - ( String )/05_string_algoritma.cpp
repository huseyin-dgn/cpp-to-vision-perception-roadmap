// 🔹 Soru 6 – Cümlenin ilk kelimesini bul (find + substr)
//
// std::string first_word(const std::string& s);
//
// İstenen:
//  - Kullanıcıdan std::getline ile bir cümle al.
//  - first_word fonksiyonu:
//      * Cümlenin başındaki ilk kelimeyi döndürsün.
//      * Kelimeler boşluk (' ') ile ayrılıyor varsay.
//      * Eğer boşluk yoksa, tüm string zaten tek kelimedir → komple döndür.
//  - main içinde:
//      * Cümleyi al
//      * first_word(s) çağır
//      * Sonucu ekrana yaz.
//
// Bu soruda özellikle göreceklerimiz:
//  - std::string::find
//  - std::string::substr
//  - std::string::npos
//  - std::getline
//  - s.size() + static_cast<int>(...)

// ------------------------------------------------------

#include <iostream>
#include <string>

std::string first_word(const std::string &s)
{
    // uzunluğu int'e çevirip bir değişkende tutalım (alışkanlık)
    int len = static_cast<int>(s.size());
    std::cout << "Metnin uzunlugu: " << len << "\n";

    // ilk boslugun konumunu bul
    // s.find(' ') -> ilk ' ' karakterinin index'i
    // eger hic yoksa std::string::npos döner
    std::size_t pos = s.find(' ');

    if (pos == std::string::npos)
    {
        // hic bosluk yok → tum string tek kelime
        return s;
    }
    else
    {
        // substr(başlangıç, uzunluk)
        // 0'dan pos'a kadar olan kısmı al
        return s.substr(0, pos);
    }
}

int main()
{
    std::string line;

    std::cout << "Bir cumle gir: ";
    std::getline(std::cin, line);

    std::string word = first_word(line);

    std::cout << "Ilk kelime: " << word << "\n";

    return 0;
}
