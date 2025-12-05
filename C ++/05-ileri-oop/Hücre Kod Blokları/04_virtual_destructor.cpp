#include <iostream>

class Base
{
public:
    Base() { std::cout << "Base Constructor\n"; }

    // Polymorphism varsa şart
    virtual ~Base()
    {
        std::cout << "Base Destructor\n";
    }
};

class Derived : public Base
{
public:
    int *dizi;

    Derived()
    {
        dizi = new int[5];
        std::cout << "Derived Constructor\n";
    }

    ~Derived()
    {
        delete[] dizi;
        std::cout << "Derived Destructor\n";
    }
};

int main()
{
    Base *ptr = new Derived();

    delete ptr; // önce Derived, sonra Base destructor çalışır

    return 0;
}
