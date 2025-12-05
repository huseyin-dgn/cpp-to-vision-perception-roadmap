#include <iostream>
class Oyuncu
{
private:
    int can;

public:
    Oyuncu(int c) : can(c) {}

    void vur()
    { // değiştirir
        can -= 10;
    }

    int getCan() const
    { // değiştirmez
        return can;
    }
};

int main()
{
    const Oyuncu p(100);

    // p.vur();       // ❌ HATA: const nesne, değiştirilemez
    std::cout << p.getCan(); // ✔ OK: const method
}
