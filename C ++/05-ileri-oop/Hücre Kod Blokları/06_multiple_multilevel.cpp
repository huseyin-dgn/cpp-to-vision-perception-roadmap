#include <iostream>

// -------------------------
// 1) Basit multilevel inheritance
// Canli -> Hayvan -> Kopek
// -------------------------

class Canli
{
public:
    void nefesAl() const
    {
        std::cout << "Canli nefes aliyor.\n";
    }
};

class Hayvan : public Canli
{
public:
    void hareketEt() const
    {
        std::cout << "Hayvan hareket ediyor.\n";
    }
};

class Kopek : public Hayvan
{
public:
    void havla() const
    {
        std::cout << "Kopek havliyor.\n";
    }
};

// -------------------------
// 2) Multiple inheritance + diamond problem çözümü
//
//       A
//      / \
//     B   C
//      \ /
//       D
//
// B ve C, A'dan VIRTUAL olarak türetiliyor.
// Böylece D içinde A'nin sadece 1 tane kopyasi olur.
// -------------------------

class A
{
public:
    int deger;

    A() : deger(0)
    {
        std::cout << "A ctor\n";
    }

    void yaz() const
    {
        std::cout << "A::deger = " << deger << "\n";
    }
};

// virtual inheritance önemli kısım:
class B : virtual public A
{
public:
    B()
    {
        std::cout << "B ctor\n";
    }
};

class C : virtual public A
{
public:
    C()
    {
        std::cout << "C ctor\n";
    }
};

class D : public B, public C
{
public:
    D()
    {
        std::cout << "D ctor\n";
        deger = 42; // A'dan gelen tek kopyaya erişiyoruz
    }
};

int main()
{
    std::cout << "=== Multilevel inheritance ===\n";
    Kopek k;
    k.nefesAl();   // Canli'dan
    k.hareketEt(); // Hayvan'dan
    k.havla();     // Kopek'e özel

    std::cout << "\n=== Multiple inheritance + virtual inheritance ===\n";
    D d;
    d.yaz(); // A'nin tek kopyasi

    return 0;
}
