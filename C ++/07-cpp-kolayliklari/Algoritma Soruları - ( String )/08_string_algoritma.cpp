// 🔹 Soru 9 – Cümledeki bir kelimenin TÜM geçişlerini sil (find + substr döngü)
//
// std::string remove_all_occurrences(std::string s, const std::string& word);
//
// İstenen:
//  - Kullanıcıdan bir cümle al (std::getline).
//  - Kullanıcıdan ayrıca silinecek kelimeyi al (cin >> word).
//  - remove_all_occurrences fonksiyonu:
//      * word kelimesinin cümlede geçtiği TÜM yerleri bulup silsin.
//      * find(...) + substr(...) işlemleri döngü içerisinde tekrarlanacak.
//      * Eğer kelime yoksa → string’i aynen döndür.
//  - Sonucu ekrana yaz.
//
// Kullanılacaklar (zorunlu):
//  - std::string
//  - std::getline
//  - s.size() + static_cast<int>(...)
//  - s.find(word)
//  - std::string::npos
//  - s.substr(...)
//  - (Yeni yok, sadece öğrendiklerimizi pekiştiriyoruz)

#include <iostream>
#include <string>

std::string remove_all_occurrences(std::string s, const std::string &word)
{
    int len = static_cast<int>(s.size());
    std::cout << "Metnin uzunlugu: " << len << "\n";

    while (true)
    {
        // kelimenin bulunduğu konum
        std::size_t pos = s.find(word);

        if (pos == std::string::npos)
        {
            // artik kelime yok → döngüyü bitir
            break;
        }

        // kelimenin sonu = pos + kelimenin uzunluğu
        std::size_t end_pos = pos + word.size();

        // kelimeden önceki kısım
        std::string before = s.substr(0, pos);

        // kelimeden sonraki kısım
        std::string after = "";
        if (end_pos < s.size())
        {
            after = s.substr(end_pos);
        }

        // birleştir: kelimeyi at
        s = before + after;
    }

    return s;
}

int main()
{
    std::string line;
    std::string word;

    std::cout << "Bir cumle gir: ";
    std::getline(std::cin, line);

    std::cout << "Silinecek kelime: ";
    std::cin >> word;

    std::string result = remove_all_occurrences(line, word);

    std::cout << "Sonuc: " << result << "\n";

    return 0;
}
