// # 📘 Ders 5 – Bölüm 1
// 🔵 Operator Overloading (Gelişmiş Operatörler)

#include <iostream>

class Vektor2D
{
public:
    int x;
    int y;

    Vektor2D(int x = 0, int y = 0)
        : x(x), y(y) {}

    // +=  (a += b)
    Vektor2D &operator+=(const Vektor2D &d)
    {
        x += d.x;
        y += d.y;
        return *this; // chaining için
    }

    // -=  (a -= b)
    Vektor2D &operator-=(const Vektor2D &d)
    {
        x -= d.x;
        y -= d.y;
        return *this;
    }

    // *=  (a *= 3)  → scalar çarpma
    Vektor2D &operator*=(int s)
    {
        x *= s;
        y *= s;
        return *this;
    }

    // ==  (a == b)
    bool operator==(const Vektor2D &d) const
    {
        return x == d.x && y == d.y;
    }

    // !=  (a != b)
    bool operator!=(const Vektor2D &d) const
    {
        return !(*this == d);
    }

    // <  (a < b)  → uzunluğa göre kıyas (x^2 + y^2)
    bool operator<(const Vektor2D &d) const
    {
        int len1 = x * x + y * y;
        int len2 = d.x * d.x + d.y * d.y;
        return len1 < len2;
    }

    // <=, >, >= diğerlerinden türetilebilir
    bool operator<=(const Vektor2D &d) const
    {
        return *this < d || *this == d;
    }

    bool operator>(const Vektor2D &d) const
    {
        return d < *this;
    }

    bool operator>=(const Vektor2D &d) const
    {
        return !(*this < d);
    }
};

int main()
{
    Vektor2D a(1, 2);
    Vektor2D b(3, 4);

    a += b; // a = (4, 6)
    a *= 2; // a = (8, 12)

    std::cout << "a: (" << a.x << ", " << a.y << ")\n";

    std::cout << "a == b ? " << (a == b) << "\n";
    std::cout << "a != b ? " << (a != b) << "\n";
    std::cout << "a <  b ? " << (a < b) << "\n";
    std::cout << "a <= b ? " << (a <= b) << "\n";
    std::cout << "a >  b ? " << (a > b) << "\n";
    std::cout << "a >= b ? " << (a >= b) << "\n";

    return 0;
}

// ****************************--------------------------*****************************************-------------

// 🚀 Move Semantics - ( Ders 5 – Bölüm 2 )

#include <iostream>

class Dizi
{
public:
    int *data;
    int boyut;

    // 1) Normal constructor
    Dizi(int b = 0)
        : boyut(b)
    {
        if (boyut > 0)
        {
            data = new int[boyut];
        }
        else
        {
            data = nullptr;
        }
        std::cout << "Normal Constructor\n";
    }

    // 2) Destructor
    ~Dizi()
    {
        delete[] data;
        std::cout << "Destructor\n";
    }

    // 3) Move Constructor
    Dizi(Dizi &&diger) noexcept
        : data(diger.data), boyut(diger.boyut)
    {
        diger.data = nullptr; // sahipligi aldik
        diger.boyut = 0;
        std::cout << "Move Constructor\n";
    }

    // 4) Move Assignment Operator
    Dizi &operator=(Dizi &&diger) noexcept
    {
        if (this != &diger)
        {
            // önce kendi eski verimizi temizle
            delete[] data;

            // sonra sahipliği devral
            data = diger.data;
            boyut = diger.boyut;

            // digeri bosalt
            diger.data = nullptr;
            diger.boyut = 0;

            std::cout << "Move Assignment\n";
        }
        return *this;
    }

    // Test için ufak bir yazdırma fonksiyonu
    void yaz() const
    {
        std::cout << "Dizi boyut: " << boyut << "\n";
    }
};

int main()
{
    std::cout << "=== a olusuyor ===\n";
    Dizi a(5);
    a.yaz();

    std::cout << "\n=== b, a'dan MOVE ile olusuyor ===\n";
    Dizi b = std::move(a); // Move Constructor
    b.yaz();
    a.yaz(); // a artik bos (boyut 0)

    std::cout << "\n=== c olusuyor ===\n";
    Dizi c(10);
    c.yaz();

    std::cout << "\n=== c'ye b MOVE ile atanıyor ===\n";
    c = std::move(b); // Move Assignment
    c.yaz();
    b.yaz(); // b artik bos

    std::cout << "\n=== main bitiyor ===\n";
    return 0;
}

// ****************************--------------------------*****************************************-------------

//  📘 Ders 5 – Bölüm 3
//  🔵 Inheritance (Kalıtım) – Temel Mantık

#include <iostream>
#include <string>

// Base class
class Karakter
{
public:
    std::string isim;
    int can;

    Karakter(const std::string &ad, int c)
        : isim(ad), can(c) {}

    void durumYaz() const
    {
        std::cout << "Isim: " << isim << " | Can: " << can << "\n";
    }
};

// Derived class
class Oyuncu : public Karakter
{
public:
    int mermi;

    Oyuncu(const std::string &ad, int c, int m)
        : Karakter(ad, c), mermi(m) {}

    void durumYazOyuncu() const
    {
        durumYaz(); // Base class fonksiyonu
        std::cout << "Mermi: " << mermi << "\n";
    }
};

int main()
{
    Oyuncu p("Cano", 100, 30);

    p.durumYaz();       // Base class fonksiyonu
    p.durumYazOyuncu(); // Derived class fonksiyonu

    return 0;
}

// ****************************--------------------------*****************************************-------------

// 📘 Ders 5 – Bölüm 4
// 🔵 Polymorphism(Çok Biçimlilik)
#include <iostream>
#include <string>

class Karakter
{
public:
    std::string isim;

    Karakter(const std::string &ad) : isim(ad) {}

    // Polymorphism için sanal fonksiyon
    virtual void hareketEt() const
    {
        std::cout << isim << " yavasca yuruyor.\n";
    }
};

class Oyuncu : public Karakter
{
public:
    Oyuncu(const std::string &ad) : Karakter(ad) {}

    // override ederek kendi davranışını yazıyor
    void hareketEt() const override
    {
        std::cout << isim << " hizlica kosuyor!\n";
    }
};

class Dusman : public Karakter
{
public:
    Dusman(const std::string &ad) : Karakter(ad) {}

    void hareketEt() const override
    {
        std::cout << isim << " saldirgan sekilde ilerliyor!\n";
    }
};

void karakteriHareketEttir(const Karakter &k)
{
    // Burada polymorphism gerçekleşiyor
    k.hareketEt();
}

int main()
{
    Oyuncu p("Cano");
    Dusman d("Zombi");

    karakteriHareketEttir(p); // Oyuncu'nun override edilmiş hali çalışır
    karakteriHareketEttir(d); // Dusman'ın override edilmiş hali çalışır

    return 0;
}

// ****************************--------------------------*****************************************-------------

// 🔥 Kod Örneği (Virtual Destructor ile – DOĞRU Kullanım)

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

// ****************************--------------------------*****************************************-------------

// Abstract Class & Pure Virtual Function (Soyut Sınıf)

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

// ****************************--------------------------*****************************************-------------

// 📘 Ders 5 – Bölüm 7
// 🔵 Multiple & Multilevel Inheritance

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
