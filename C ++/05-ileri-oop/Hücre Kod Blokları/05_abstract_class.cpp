#include <iostream>
#include <cmath>

// Soyut base sınıf (abstract class)
class Sekil
{
public:
    // Pure virtual fonksiyon → bu sınıf soyut olur
    virtual double alan() const = 0;
    virtual void yaz() const = 0;

    // Polymorphic kullanım varsa destructor'ı virtual yapmak iyi alışkanlık
    virtual ~Sekil() {}
};

// Derived: Dikdörtgen
class Dikdortgen : public Sekil
{
private:
    double genislik;
    double yukseklik;

public:
    Dikdortgen(double g, double y)
        : genislik(g), yukseklik(y) {}

    double alan() const override
    {
        return genislik * yukseklik;
    }

    void yaz() const override
    {
        std::cout << "Dikdortgen | Genislik: " << genislik
                  << " Yukseklik: " << yukseklik
                  << " Alan: " << alan() << "\n";
    }
};

// Derived: Cember
class Cember : public Sekil
{
private:
    double yaricap;

public:
    Cember(double r)
        : yaricap(r) {}

    double alan() const override
    {
        return 3.14159 * yaricap * yaricap;
    }

    void yaz() const override
    {
        std::cout << "Cember     | Yaricap: " << yaricap
                  << " Alan: " << alan() << "\n";
    }
};

int main()
{
    // Soyut sınıftan NESNE OLMAZ:
    // Sekil s;          // ❌ HATA
    // Sekil s2 = Cember(5.0); // ❌ HATA (slicing + abstract)

    // Ama base pointer ile derived nesneleri tutabilirsin:
    Sekil *s1 = new Dikdortgen(3.0, 4.0);
    Sekil *s2 = new Cember(5.0);

    s1->yaz(); // Dikdortgen'in versiyonu
    s2->yaz(); // Cember'in versiyonu

    delete s1;
    delete s2;

    return 0;
}
