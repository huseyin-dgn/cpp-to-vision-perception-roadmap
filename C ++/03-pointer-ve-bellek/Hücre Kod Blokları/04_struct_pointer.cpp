// %% DERS 3 – Bolum 5 (Pointer & Struct)

#include <iostream>

struct Arac
{
    int hiz;
    float motorSicakligi;
    bool arıza;
};

int main()
{
    Arac a;
    a.hiz = 80;
    a.motorSicakligi = 95.3f;
    a.arıza = false;

    Arac *p = &a;

    std::cout << "Normal erisim: " << std::endl;
    std::cout << "Hiz: " << a.hiz << std::endl;
    std::cout << "Motor sicakligi: " << a.motorSicakligi << std::endl;
    std::cout << "Ariza: " << a.arıza << std::endl;

    std::cout << "\nPointer ile erisim (->): " << std::endl;
    std::cout << "Hiz: " << p->hiz << std::endl;
    std::cout << "Motor sicakligi: " << p->motorSicakligi << std::endl;
    std::cout << "Ariza: " << p->arıza << std::endl;

    p->hiz = 120;
    p->arıza = true;

    std::cout << "\nGuncellenmis degerler:" << std::endl;
    std::cout << "Hiz: " << a.hiz << std::endl;
    std::cout << "Ariza: " << a.arıza << std::endl;

    return 0;
}

// --------- BİR ÖRNEK DAHA ---------

// %% DERS 3 – Bolum 5 Mini Gorev (Struct + Pointer + ->)
#include <iostream>
#include <string>

struct Sensor
{
    std::string ad;
    float deger;
    bool aktif;
};

int main()
{
    // 1) Normal struct nesnesi olustur
    Sensor s;
    s.ad = "Motor Sicaklik Sensore";
    s.deger = 92.5f;
    s.aktif = true;

    // 2) Struct pointer olustur
    Sensor *ps = &s;

    std::cout << "Normal erisim (s.ad):      " << s.ad << std::endl;
    std::cout << "Pointer ile erisim (ps->ad): " << ps->ad << std::endl;

    std::cout << "\nIlk deger (s.deger): " << s.deger << std::endl;

    // 3) Degeri pointer uzerinden degistir
    ps->deger = 100.0f;

    std::cout << "Pointer ile guncel deger (ps->deger): " << ps->deger << std::endl;
    std::cout << "Struct uzerinden kontrol (s.deger):   " << s.deger << std::endl;

    return 0;
}
