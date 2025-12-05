#include <iostream>
#include <string>

class Araba
{
private:
    int hiz;
    int motorSicakligi;

public:
    Araba(int h, int s)
        : hiz(h), motorSicakligi(s) {}

    // 1) Belirli bir fonksiyona özel izin
    friend void yazDetay(const Araba &a);

    // 2) Bir sınıfa tam erişim izni
    friend class Polis;
};

// ---------------------------
// Friend Function
// ---------------------------
void yazDetay(const Araba &a)
{
    // Normalde private alanlara erişilemezdi ama friend olduğu için erişiyor
    std::cout << "[Friend Function] Hiz: " << a.hiz
              << " | Sicaklik: " << a.motorSicakligi << "\n";
}

// ---------------------------
// Friend Class
// ---------------------------
class Polis
{
public:
    void radar(const Araba &a)
    {
        std::cout << "[Friend Class] Aracin hizi: " << a.hiz << "\n";
    }

    void motorKontrol(const Araba &a)
    {
        std::cout << "[Friend Class] Motor sicakligi: "
                  << a.motorSicakligi << "\n";
    }
};

int main()
{
    Araba a(120, 95);
    Polis p;

    // Friend function çalışıyor:
    yazDetay(a);

    // Friend class tüm private verilere erişebilir:
    p.radar(a);
    p.motorKontrol(a);

    return 0;
}
