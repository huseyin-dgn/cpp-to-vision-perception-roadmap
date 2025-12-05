#include <iostream>

class Oyuncu
{
private:
    int can;

public:
    Oyuncu(int baslangicCan)
        : can(baslangicCan) {}

    // NESNEYİ DEĞİŞTİREN METHOD (non-const)
    void hasarAl(int miktar)
    {
        can -= miktar;
        if (can < 0)
            can = 0;
    }

    // SADECE OKUYAN METHOD (const)
    int getCan() const
    {
        return can; // sadece okuyor, değiştirmiyor
    }
};

// Dışarıda, const referans alan bir fonksiyon
void yazRapor(const Oyuncu &o)
{
    // sadece const method çağırabilir
    std::cout << "Rapor - Can: " << o.getCan() << "\n";
    // o.hasarAl(10); // HATA: const üstünden non-const method çağıramazsın
}

int main()
{
    Oyuncu p(100);

    p.hasarAl(30);                   // nesne değişti
    std::cout << p.getCan() << "\n"; // const method → sadece okur

    yazRapor(p); // dışarıdan sadece okuyabilen fonksiyon

    return 0;
}
