#include <iostream>
#include <memory>

class Nesne
{
public:
    Nesne() { std::cout << "Dogdu\n"; }
    ~Nesne() { std::cout << "Oluyor...\n"; }
};

int main()
{
    {
        Nesne a; // STACK → dogdu → scope bitince oluyor
    }

    {
        Nesne *b = new Nesne(); // HEAP → dogdu
        delete b;               // manuel oluyor
    }

    {
        auto c = std::make_unique<Nesne>(); // HEAP + otomatik RAII
    } // burada otomatik oluyor

    return 0;
}
