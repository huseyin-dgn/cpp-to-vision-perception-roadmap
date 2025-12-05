// 🔹 Soru 8 – Cümledeki bir kelimenin İLK geçişini sil (find + substr)
//
// std::string remove_first_occurrence(const std::string& s, const std::string& word);
//
// İstenen:
//  - Kullanıcıdan std::getline ile bir cümle al.
//  - Kullanıcıdan ayrıca silmek istediği bir kelime al (cin >> word).
//  - remove_first_occurrence:
//      * s içinde word'ün İLK geçtiği yeri bulsun (s.find(word)).
//      * Eğer hiç yoksa → s'yi aynen döndürsün.
//      * Varsa:
//          - o kelimeyi cümleden çıkarsın
//          - geri kalan parçaları birleştirip yeni string döndürsün.
//  - main içinde sonucu ekrana yaz.
//
// Kullanılacaklar (zorunlu):
//  - std::string
//  - std::getline(std::cin, s)
//  - s.size() + static_cast<int>(...)
//  - s.find(word)
//  - std::string::npos
//  - s.substr(...)

// 🔹 Soru 8 – Cümledeki bir kelimenin İLK geçişini sil (find + substr)
//
// std::string remove_first_occurrence(const std::string& s, const std::string& word);
//
// İstenen:
//  - Kullanıcıdan std::getline ile bir cümle al.
//  - Kullanıcıdan ayrıca silmek istediği bir kelime al (cin >> word).
//  - remove_first_occurrence:
//      * s içinde word'ün İLK geçtiği yeri bulsun (s.find(word)).
//      * Eğer hiç yoksa → s'yi aynen döndürsün.
//      * Varsa:
//          - o kelimeyi cümleden çıkarsın
//          - geri kalan parçaları birleştirip yeni string döndürsün.
//  - main içinde sonucu ekrana yaz.
//
// Kullanılacaklar (zorunlu):
//  - std::string
//  - std::getline(std::cin, s)
//  - s.size() + static_cast<int>(...)
//  - s.find(word)
//  - std::string::npos
//  - s.substr(...)

#include <iostream>
#include <string>

std::string remove_first_occurrence(const std::string &s, const std::string &word)
{
    int len = static_cast<int>(s.size());
    std::cout << "Metnin uzunlugu: " << len << "\n";

    // word'ün s içinde ilk geçtiği konum
    std::size_t pos = s.find(word);

    if (pos == std::string::npos)
    {
        // kelime yok → aynen geri dön
        return s;
    }

    // kelimenin bittiği pozisyon = baslangic + kelimenin uzunlugu
    std::size_t end_pos = pos + word.size();

    // 1. parça: kelimeden ÖNCEKİ kısım
    std::string before = s.substr(0, pos);

    // 2. parça: kelimeden SONRAKİ kısım
    std::string after;
    if (end_pos < s.size())
    {
        after = s.substr(end_pos); // end_pos'tan sona kadar
    }
    else
    {
        after = ""; // kelime sondaysa sonrası yok
    }

    // Basitçe birleştir (istersen aradaki fazladan boşlukları sonra temizleyebilirsin)
    std::string result = before + after;
    return result;
}

int main()
{
    std::string line;
    std::string word;

    std::cout << "Bir cumle gir: ";
    std::getline(std::cin, line);

    std::cout << "Silmek istedigin kelimeyi gir: ";
    std::cin >> word;

    std::string result = remove_first_occurrence(line, word);

    std::cout << "Sonuc: " << result << "\n";

    return 0;
}
