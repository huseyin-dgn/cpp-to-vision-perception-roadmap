#include <iostream>
#include <string>

class Karakter
{
public:
    std::string isim;

    Karakter(const std::string &ad) : isim(ad) {}

    // Polymorphism için sanal fonksiyon
    virtual void hareketEt() const
    {
        std::cout << isim << " yavasca yuruyor.\n";
    }
};

class Oyuncu : public Karakter
{
public:
    Oyuncu(const std::string &ad) : Karakter(ad) {}

    // override ederek kendi davranışını yazıyor
    void hareketEt() const override
    {
        std::cout << isim << " hizlica kosuyor!\n";
    }
};

class Dusman : public Karakter
{
public:
    Dusman(const std::string &ad) : Karakter(ad) {}

    void hareketEt() const override
    {
        std::cout << isim << " saldirgan sekilde ilerliyor!\n";
    }
};

void karakteriHareketEttir(const Karakter &k)
{
    // Burada polymorphism gerçekleşiyor
    k.hareketEt();
}

int main()
{
    Oyuncu p("Cano");
    Dusman d("Zombi");

    karakteriHareketEttir(p); // Oyuncu'nun override edilmiş hali çalışır
    karakteriHareketEttir(d); // Dusman'ın override edilmiş hali çalışır

    return 0;
}
