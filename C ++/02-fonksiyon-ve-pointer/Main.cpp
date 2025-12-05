#include <iostream>

// 1) Pointer Nedir
void demoPointerNedir()
{
    int sayi = 42;
    int *p = &sayi;

    std::cout << "\n--- Pointer Nedir ---\n";
    std::cout << "sayi: " << sayi << "\n";
    std::cout << "sayi'nin adresi (&sayi): " << &sayi << "\n";
    std::cout << "p (tuttugu adres): " << p << "\n";
    std::cout << "*p (gosterdigi deger): " << *p << "\n";
}

// 2) Bellek Adresi
void demoBellekAdresi()
{
    int x = 10;

    std::cout << "\n--- Bellek Adresi (&) ---\n";
    std::cout << "x'in adresi: " << &x << "\n";
}

// 3) Dereference
void demoDereference()
{
    int x = 15;
    int *p = &x;

    std::cout << "\n--- Dereference (*) ---\n";
    std::cout << "x: " << x << "\n";
    std::cout << "*p: " << *p << "\n";
    *p = 99; // pointer üzerinden değer değiştirme
    std::cout << "Pointer ile x degistirildi! Yeni x: " << x << "\n";
}

// 4) Value / Reference / Pointer
void arttirValue(int x) { x += 10; }
void arttirRef(int &x) { x += 10; }
void arttirPtr(int *x) { *x += 10; }

void demoValueRefPtr()
{
    int sayi = 5;

    std::cout << "\n--- Value / Reference / Pointer ---\n";
    std::cout << "Baslangic sayi: " << sayi << "\n";

    arttirValue(sayi);
    std::cout << "Value sonrasi: " << sayi << "\n";

    arttirRef(sayi);
    std::cout << "Reference sonrasi: " << sayi << "\n";

    arttirPtr(&sayi);
    std::cout << "Pointer sonrasi: " << sayi << "\n";
}

// 5) nullptr güvenliği
void yazdir(int *p)
{
    if (p == nullptr)
    {
        std::cout << "Pointer bos (nullptr)\n";
        return;
    }
    std::cout << "Deger: " << *p << "\n";
}

void demoNullptr()
{
    int x = 77;
    int *p1 = &x;
    int *p2 = nullptr;

    std::cout << "\n--- nullptr Guvenligi ---\n";

    yazdir(p1);
    yazdir(p2);
}

// 6) Dangling Pointer
int *olustur()
{
    int x = 10; // stack değişkeni
    return &x;  // ❌ fonksiyon bitince x yok olur -> dangling
}

void demoDangling()
{
    std::cout << "\n--- Dangling Pointer ---\n";

    int *p = olustur();
    std::cout << "Gecersiz adres: " << p << "\n";
    std::cout << "Bu adresin degerini okumak COK TEHLIKELI!\n";

    // *p   // bilerek çalıştırmıyoruz, crash olur
}

// 7) Wild Pointer
void demoWildPointer()
{
    std::cout << "\n--- Wild Pointer ---\n";

    int *p; // ❌ baslangic yok -> wild pointer
    std::cout << "Wild pointer adres: " << p << "\n";
    std::cout << "Dereference etmek tehlikelidir. (*p KULLANMA)\n";
    // std::cout << *p; // bilerek çalıştırmıyorum
}

// ------------------------------------------------------------
// Menü
// ------------------------------------------------------------
void menu()
{
    std::cout << "\n==============================\n";
    std::cout << "  POINTER TEMELLERİ DEMO MENÜSÜ\n";
    std::cout << "==============================\n";
    std::cout << "1) Pointer Nedir\n";
    std::cout << "2) Bellek Adresi (&)\n";
    std::cout << "3) Dereference (*)\n";
    std::cout << "4) Value vs Ref vs Pointer\n";
    std::cout << "5) nullptr Güvenliği\n";
    std::cout << "6) Dangling Pointer\n";
    std::cout << "7) Wild Pointer\n";
    std::cout << "0) Cikis\n";
    std::cout << "Secim: ";
}

int main()
{
    while (true)
    {
        menu();
        int secim;
        std::cin >> secim;

        switch (secim)
        {
        case 1:
            demoPointerNedir();
            break;
        case 2:
            demoBellekAdresi();
            break;
        case 3:
            demoDereference();
            break;
        case 4:
            demoValueRefPtr();
            break;
        case 5:
            demoNullptr();
            break;
        case 6:
            demoDangling();
            break;
        case 7:
            demoWildPointer();
            break;
        case 0:
            std::cout << "Cikis yapiliyor...\n";
            return 0;
        default:
            std::cout << "Hatali secim!\n";
            break;
        }
    }
}
