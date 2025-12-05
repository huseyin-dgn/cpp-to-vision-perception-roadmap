// Ders 4 – Bölüm 2  --- Public / Private / Protected (Erişim Belirleyicileri)

#include <iostream>
#include <string>

class Oyuncu
{
public:
    std::string isim;

private:
    int can;
    int mermi;

public:
    void ayarla(int yeniCan, int yeniMermi)
    {
        can = yeniCan;
        mermi = yeniMermi;
    }

    void durumYaz()
    {
        std::cout << "Oyuncu: " << isim
                  << " | Can: " << can
                  << " | Mermi: " << mermi
                  << std::endl;
    }
};

int main()
{
    Oyuncu p1;

    p1.isim = "Cano"; // public → OK
    // p1.can = 100;      // private → HATA
    // p1.mermi = 30;     // private → HATA

    p1.ayarla(100, 30); // OK, çünkü ayarla() public
    p1.durumYaz();

    return 0;
}
