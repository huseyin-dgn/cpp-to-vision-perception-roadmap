// 🔹 Soru 5 – Cümlede kaç harf, kaç rakam, kaç boşluk var?
//
// void analyze_text(const std::string& s, int& letter_count, int& digit_count, int& space_count);
//
// İstenen:
//  - Kullanıcıdan std::getline ile bir cümle al.
//  - analyze_text fonksiyonu:
//      * s içindeki harf sayısını (a-z, A-Z) letter_count içine yazsın.
//      * s içindeki rakam sayısını (0-9) digit_count içine yazsın.
//      * s içindeki boşluk sayısını (space ' ') space_count içine yazsın.
//  - main içinde bu fonksiyonu çağır ve sonuçları ekrana yaz.
//
// Kullanılacaklar (zorunlu):
//  - std::string
//  - std::getline(std::cin, s)
//  - s.size() + static_cast<int>(...)
//  - range-based for: for (auto c : s) { ... } veya for (auto& c : s)
//  - std::isalpha(...)
//  - std::isdigit(...)
//  - std::isspace(...)
//  - isalpha/isdigit/isspace çağrılarında unsigned char cast

#include <iostream>
#include <string>
#include <cctype> // isalpha, isdigit, isspace

void analyze_text(const std::string &s,
                  int &letter_count,
                  int &digit_count,
                  int &space_count)
{
    letter_count = 0;
    digit_count = 0;
    space_count = 0;

    int len = static_cast<int>(s.size());
    std::cout << "Metnin uzunlugu: " << len << "\n";

    for (auto c : s)
    {
        unsigned char uc = static_cast<unsigned char>(c);

        if (std::isalpha(uc))
        {
            letter_count++;
        }
        else if (std::isdigit(uc))
        {
            digit_count++;
        }
        else if (std::isspace(uc))
        {
            space_count++;
        }
        // Diğer karakterler (.,!?, vs) için bir şey yapmıyoruz.
    }
}

int main()
{
    std::string line;

    std::cout << "Bir cumle gir: ";
    std::getline(std::cin, line);

    int letters = 0;
    int digits = 0;
    int spaces = 0;

    analyze_text(line, letters, digits, spaces);

    std::cout << "Harf sayisi : " << letters << "\n";
    std::cout << "Rakam sayisi: " << digits << "\n";
    std::cout << "Bosluk sayisi: " << spaces << "\n";

    return 0;
}
