#include <iostream>
#include <string>

class Oyuncu
{
public:
    std::string isim;
    int can;
    int mermi;

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
    Oyuncu p1; // 1) Nesne oluşturduk (STACK üzerinde)

    p1.isim = "Cano"; // 2) Alanlara değer atadık
    p1.can = 100;
    p1.mermi = 30;

    p1.durumYaz(); // 3) Method çağırdık

    return 0;
}
