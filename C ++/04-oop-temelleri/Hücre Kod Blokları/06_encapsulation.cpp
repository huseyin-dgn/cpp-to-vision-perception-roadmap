#include <iostream>

class Oyuncu
{
private:
    int can; // dışarıdan erişilemez

public:
    // SETTER → değeri değiştirmeye izin verir
    void setCan(int yeniCan)
    {
        if (yeniCan < 0)
            yeniCan = 0; // kontrol ekledik
        can = yeniCan;
    }

    // GETTER → değeri OKUMAYA izin verir
    int getCan() const
    {
        return can; // veri sadece okunuyor
    }
};

int main()
{
    Oyuncu p;

    p.setCan(100);           // kontrol bizde
    std::cout << p.getCan(); // 100

    p.setCan(-50);           // setter kontrol ettiği için 0 olur
    std::cout << p.getCan(); // 0
}
