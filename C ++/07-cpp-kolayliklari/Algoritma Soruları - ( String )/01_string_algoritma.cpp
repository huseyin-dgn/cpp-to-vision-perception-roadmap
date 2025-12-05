// 🔹 Soru 2 – Bir karakterin string içinde kaç kere geçtiğini bul
//
// int count_char(const std::string& s, char target);
//
// İstenen:
//  - Kullanıcıdan bir kelime (string) al.
//  - Kullanıcıdan ayrıca aranacak bir karakter al (örneğin: 'a').
//  - count_char fonksiyonu, s içinde target karakterinin kaç kere geçtiğini döndürsün.
//  - main içinde bu fonksiyonu çağır ve sonucu ekrana yazdır.
//
// Kullanılacaklar (zorunlu):
//  - std::string
//  - s.size()
//  - static_cast<int>(s.size()) veya benzer bir static_cast kullanımı
//  - range-based for:  for (auto c : s) { ... }
//
// Örnek:
//  s = "merhaba", target = 'a'  → sonuç: 2

#include <iostream>
#include <string>

// s içinde target karakterinin kaç kez geçtiğini sayan fonksiyon
int count_char(const std::string &s, char target)
{
    int count = 0;

    // string uzunluğunu static_cast ile int'e çeviriyoruz
    int len = static_cast<int>(s.size());
    std::cout << "String uzunlugu (len): " << len << "\n";

    // s içindeki her karakteri sırayla geziyoruz
    for (auto c : s)
    {
        if (c == target)
        {
            count++;
        }
    }

    return count;
}

int main()
{
    std::string text;
    char ch;

    std::cout << "Bir kelime gir: ";
    std::cin >> text;

    std::cout << "Saymak istedigin karakteri gir: ";
    std::cin >> ch;

    int result = count_char(text, ch);

    std::cout << "'" << ch << "' karakteri, \"" << text
              << "\" ifadesinde " << result << " kez geciyor.\n";

    return 0;
}
