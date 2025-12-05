#include <iostream>

class Sayaç
{
private:
    int *deger; // heap'te tutulacak

public:
    // Constructor
    Sayaç(int baslangic)
    {
        std::cout << "Constructor: Sayaç olusturuluyor...\n";
        deger = new int(baslangic); // HEAP'te int açtık
    }

    void arttir()
    {
        (*deger)++;
    }

    void yaz() const
    {
        std::cout << "Sayaç degeri: " << *deger << "\n";
    }

    // Destructor
    ~Sayaç()
    {
        std::cout << "Destructor: Beéllek serbest birakiliyor...\n";
        delete deger; // HEAP'teki int'i siliyoruz
    }
};

int main()
{
    {
        Sayaç s(10); // constructor burada
        s.yaz();
        s.arttir();
        s.yaz();
    } // scope biter → destructor burada otomatik çalışır

    std::cout << "Main devam ediyor...\n";
    return 0;
}
