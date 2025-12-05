#include <iostream>

class SınıfAdi
{
public:
    // 1) STATIC DEĞİŞKEN (class-level, ortak)
    static int ortakSayac;

    // 2) NORMAL ÜYE DEĞİŞKEN (her nesnenin kendi değeri)
    int deger;

    // 3) Constructor
    SınıfAdi(int d)
        : deger(d)
    {
        ortakSayac++; // her nesne oluşunca artar
    }

    // 4) STATIC METHOD (nesnesiz çağrılır)
    static void ortakBilgiYaz()
    {
        std::cout << "Toplam nesne sayisi: " << ortakSayac << "\n";

        // std::cout << deger;  // ❌ HATA: non-static üyeye erişemez
    }

    // 5) Normal method (nesne üzerinden çağrılır)
    void yaz() const
    {
        std::cout << "Nesne degeri: " << deger << "\n";
    }
};

// 6) static değişkenin class dışındaki TANIMI
int SınıfAdi::ortakSayac = 0;

int main()
{
    SınıfAdi a(10);
    SınıfAdi b(20);

    a.yaz(); // nesne methodu
    b.yaz();

    SınıfAdi::ortakBilgiYaz(); // static method → sınıf üzerinden

    return 0;
}
