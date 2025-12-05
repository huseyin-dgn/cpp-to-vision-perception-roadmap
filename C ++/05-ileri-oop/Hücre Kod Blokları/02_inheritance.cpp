#include <iostream>
#include <string>

// Base class
class Karakter
{
public:
    std::string isim;
    int can;

    Karakter(const std::string &ad, int c)
        : isim(ad), can(c) {}

    void durumYaz() const
    {
        std::cout << "Isim: " << isim << " | Can: " << can << "\n";
    }
};

// Derived class
class Oyuncu : public Karakter
{
public:
    int mermi;

    Oyuncu(const std::string &ad, int c, int m)
        : Karakter(ad, c), mermi(m) {}

    void durumYazOyuncu() const
    {
        durumYaz(); // Base class fonksiyonu
        std::cout << "Mermi: " << mermi << "\n";
    }
};

int main()
{
    Oyuncu p("Cano", 100, 30);

    p.durumYaz();       // Base class fonksiyonu
    p.durumYazOyuncu(); // Derived class fonksiyonu

    return 0;
}
