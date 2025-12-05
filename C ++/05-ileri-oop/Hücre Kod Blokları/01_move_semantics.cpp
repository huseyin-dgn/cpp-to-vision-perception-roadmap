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
