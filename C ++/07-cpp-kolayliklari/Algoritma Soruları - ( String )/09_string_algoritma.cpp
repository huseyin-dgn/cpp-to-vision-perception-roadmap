// 🔹 Tek Dosyada String Ameliyatı Örneği
// Bu örnekte şunları TEK KOD içinde kullanıyoruz:
//  - std::string
//  - s.erase(pos, length)
//  - s.replace(pos, length, yeni_metin)
//  - s.find("..."), s.find("...", start_pos)
//  - std::string::npos
//  - s.rfind("...")
//  - s.begin(), s.end()
//  - std::reverse
//  - std::transform
//  - std::stringstream (cümleyi kelimelere bölmek için)

// 🔹 Tek Dosyada String Ameliyatı Örneği
// Bu örnekte şunları TEK KOD içinde kullanıyoruz:
//  - std::string
//  - s.erase(pos, length)
//  - s.replace(pos, length, yeni_metin)
//  - s.find("..."), s.find("...", start_pos)
//  - std::string::npos
//  - s.rfind("...")
//  - s.begin(), s.end()
//  - std::reverse
//  - std::transform
//  - std::stringstream (cümleyi kelimelere bölmek için)

#include <iostream>
#include <string>
#include <algorithm> // std::reverse, std::transform
#include <cctype>    // std::toupper
#include <sstream>   // std::stringstream

int main()
{
    // Başlangıç cümlemiz:
    std::string s = "Merhaba dunya nasilsin dunya bugun?";

    std::cout << "Orijinal:    " << s << "\n\n";

    // 1) erase(pos, length)
    // 0. indexten itibaren 3 karakteri sil → "Mer" gider.
    s.erase(0, 3);
    std::cout << "erase(0,3):  " << s << "\n"; // "haba dunya nasilsin dunya bugün?"

    // 2) replace(pos, length, yeni_metin)
    // İlk "dunya" kelimesini bulup yerine "DUNYA" yazalım.
    std::size_t first_world = s.find("dunya"); // soldan ilk "dunya"
    if (first_world != std::string::npos)
    {
        s.replace(first_world, 5, "DUNYA"); // "dunya" 5 harf
    }
    std::cout << "replace 1.:  " << s << "\n"; // "haba DUNYA nasilsin dunya bugün?"

    // 3) find("kelime", start_pos)
    // Aynı kelimeyi bu sefer ilk bulduğumuz yerden SONRA arayalım (ikinci "dunya").
    std::size_t second_world = s.find("dunya", first_world + 1);
    if (second_world != std::string::npos)
    {
        s.replace(second_world, 5, "DUNYA2");
    }
    std::cout << "replace 2.:  " << s << "\n"; // "haba DUNYA nasilsin DUNYA2 bugün?"

    // 4) rfind("...") – sağdan arama
    // "DUNYA" kelimesinin SON geçtiği yeri bulalım.
    std::size_t last_dunya = s.rfind("DUNYA");
    if (last_dunya != std::string::npos)
    {
        std::cout << "rfind DUNYA index: " << last_dunya << "\n";
    }
    std::cout << "\n";

    // 5) reverse(begin, end) – stringi ters çevir
    std::string reversed = s; // kopya al
    std::reverse(reversed.begin(), reversed.end());
    std::cout << "reverse:     " << reversed << "\n";

    // 6) transform(begin, end, hedef_begin, fonksiyon)
    // Tüm karakterleri BÜYÜK harfe çevirelim.
    std::string upper = s;
    std::transform(
        upper.begin(), upper.end(), // kaynak aralık
        upper.begin(),              // hedef (aynı string üstüne yazıyoruz)
        [](unsigned char c) {       // lambda: her karakter için çalışır
            return static_cast<char>(std::toupper(c));
        });
    std::cout << "transform:   " << upper << "\n";

    // 7) stringstream – cümleyi kelimelere böl
    std::stringstream ss(s); // s içinden kelimeleri okuyacağız
    std::string word;

    std::cout << "\nKelime kelime:\n";
    while (ss >> word)
    {
        std::cout << "- " << word << "\n";
    }

    return 0;
}
