#include <iostream>
// struct → default: public
struct OyuncuStruct
{
    int can;   // public
    int mermi; // public
};

// class → default: private
class OyuncuClass
{
    int can;   // private
    int mermi; // private
public:
    void ayarla(int c, int m)
    {
        can = c;
        mermi = m;
    }
    void yaz() const
    {
        std::cout << "Can: " << can << ", Mermi: " << mermi << "\n";
    }
};

int main()
{
    OyuncuStruct s;
    s.can = 100; // ✅ direk erişebiliyorsun (public)
    s.mermi = 30;

    std::cout << s.can << " " << s.mermi << "\n";

    OyuncuClass c;
    // c.can = 100;      // ❌ hata: private
    c.ayarla(100, 30); // ✅ public method üzerinden ayar
    c.yaz();

    return 0;
}
