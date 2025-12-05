// Ders 4 – Bölüm 3 → Constructor (Kurucu Fonksiyon)
// 🔥 En basit örnek

#include <iostream>
#include <string>

class Oyuncu3
{
public:
    std::string isim_3;
    int can_3;
    int mermi_3;

    Oyuncu3()
    {
        can_3 = 100;
        mermi_3 = 30;
        std::cout << "Oyuncu oluşturuldu \n";
    }

    void DurumYaz()
    {
        std::cout << isim_3 << "| Can : " << can_3
                  << "| Mermi : " << mermi_3 << "\n";
    }
};

int main()
{
    Oyuncu3 p3;
    p3.isim_3 = "Hyso";
    p3.DurumYaz();
}

// ⭐ Parametreli Constructor -- Nesneyi oluştururken direkt değer vermek istiyorsan:

class Oyuncu4
{
public:
    std::string isim_4;
    int can_4;
    int mermi_4;

    Oyuncu4(std::string ad, int c, int m)
    {
        isim_4 = ad;
        can_4 = c;
        mermi_4 = m;
    }
};