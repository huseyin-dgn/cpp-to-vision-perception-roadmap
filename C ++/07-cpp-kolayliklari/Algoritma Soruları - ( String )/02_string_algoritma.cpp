// 🔹 Soru 3 – Cümleyi tamamen BÜYÜK harfe çevir
//
// std::string to_upper_sentence(std::string s);
//
// İstenen:
//  - Kullanıcıdan boşluk içerebilen bir cümle al (örneğin: "merhaba dünya nasilsin").
//  - to_upper_sentence fonksiyonu bu cümleyi tamamen BÜYÜK harfe çevirip döndürsün.
//  - main içinde:
//      * Kullanıcıdan cümleyi std::getline ile al
//      * Fonksiyonu çağır
//      * Sonucu ekrana yazdır
//
// Kullanılacaklar (yeni + eskiler):
//  - std::string
//  - std::getline(std::cin, s)
//  - for (auto& c : s) { ... }   // referans ile gez, karakteri yerinde değiştir
//  - std::toupper(c)
//  - s.size() (isteğe bağlı, en az bir yerde kullan)
//  - static_cast<int>(...) (en az 1 kez göster)

#include <iostream>
#include <string>
#include <cctype> // std::toupper

// Cümleyi tamamen büyük harfe çeviren fonksiyon
std::string to_upper_sentence(std::string s)
{
    // uzunluğu bir görelim diye static_cast kullanalım
    int len = static_cast<int>(s.size());
    std::cout << "Cumlenin uzunlugu: " << len << "\n";

    // auto&: her karakteri REFERANS ile alıyoruz
    // böylece c'yi değiştirince s içindeki karakter de değişiyor
    for (auto &c : s)
    {
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        // yukarıda ufak güvenli cast kombosu var:
        // unsigned char -> toupper -> char
    }

    return s;
}

int main()
{
    std::string line;

    std::cout << "Bir cumle gir: ";
    std::getline(std::cin, line); // bosluklari da al

    std::string upper = to_upper_sentence(line);

    std::cout << "Buyuk harf hali: " << upper << "\n";

    return 0;
}
