#include <iostream>

class Oyuncu
{
private:
    int can;
    int mermi;

public:
    // 1) Parametreyle class değişkeni aynı isimde → this zorunlu
    void ayarla(int can, int mermi)
    {
        this->can = can; // sol: class değişkeni, sağ: parametre
        this->mermi = mermi;
    }

    // 2) "this" olmadan ne olur?
    void ayarlaYanlis(int can, int mermi)
    {
        can = can;     // tamamen gereksiz, parametre kendi kendine atanıyor
        mermi = mermi; // class değişkenleri değişmiyor
    }

    // 3) this ile method chaining yapma
    Oyuncu &arttir()
    {
        this->can++; // "bu nesnenin" can değerini arttır
        this->mermi++;
        return *this; // .arttir().arttir() zinciri için
    }

    void yaz() const
    {
        std::cout << "Can: " << can << ", Mermi: " << mermi << "\n";
    }
};

int main()
{
    Oyuncu p;

    p.ayarla(100, 30);
    p.yaz(); // Can: 100, Mermi: 30

    p.ayarlaYanlis(200, 50);
    p.yaz(); // HÂLÂ Can: 100, Mermi: 30  (yanlış method hiçbir işe yaramadı)

    p.arttir().arttir().arttir(); // method chaining
    p.yaz();                      // Can: 103, Mermi: 33

    return 0;
}
