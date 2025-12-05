// 🔹 Soru 7 – Cümlenin ilk kelimesini at, geri kalanı döndür (find + substr tekrar)
//
// std::string drop_first_word(const std::string& s);
//
// İstenen:
//  - Kullanıcıdan std::getline ile bir cümle al.
//  - drop_first_word fonksiyonu:
//      * Cümlenin ilk kelimesini atıp, geri kalan kısmı döndürsün.
//      * Kelimeler boşluk (' ') ile ayrılıyor varsay.
//      * Eğer hiç boşluk yoksa, yani tek kelimeyse → boş string ("") döndür.
//  - main içinde:
//      * Cümleyi al
//      * Hem ilk kelimeyi, hem de kalanı ekrana yaz (ilk kelimeyi bulmak için yine find+substr kullanabilirsin).
//
// Kullanılacaklar (zorunlu):
//  - std::string
//  - std::getline(std::cin, s)
//  - s.size() + static_cast<int>(...)
//  - s.find(' ')
//  - std::string::npos
//  - s.substr(...)

#include <iostream>
#include <string>

std::string drop_first_word(const std::string &s)
{
    int len = static_cast<int>(s.size());
    std::cout << "Metnin uzunlugu: " << len << "\n";

    std::size_t pos = s.find(' '); // ilk boslugun yeri

    if (pos == std::string::npos)
    {
        // hic bosluk yok → tek kelime → geriye bir şey kalmıyor
        return "";
    }
    else
    {
        // pos: ilk boslugun index'i
        // pos + 1: bosluktan SONRASI (yani ikinci kelimenin basi)
        return s.substr(pos + 1);
    }
}

std::string first_word(const std::string &s)
{
    std::size_t pos = s.find(' ');

    if (pos == std::string::npos)
    {
        // hic bosluk yoksa → komple kelime
        return s;
    }
    else
    {
        // bastan ilk bosluga kadar
        return s.substr(0, pos);
    }
}

int main()
{
    std::string line;

    std::cout << "Bir cumle gir: ";
    std::getline(std::cin, line);

    std::string first = first_word(line);
    std::string rest = drop_first_word(line);

    std::cout << "Ilk kelime    : " << first << "\n";
    std::cout << "Geri kalan    : " << rest << "\n";

    return 0;
}
