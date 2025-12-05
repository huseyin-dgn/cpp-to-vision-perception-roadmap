// %% DERS 2 — Hücre 11 (Value vs Reference vs Pointer Kıyas Kodu)

// %% DERS 2 — Hücre 11 (Value vs Reference vs Pointer Kıyas Kodu)

#include <iostream>

void arttirValue(int x)
{ // VALUE: Kopya ile çalışır
    x = x + 10;
    std::cout << "[Value]  Fonksiyon icindeki x: " << x << std::endl;
}

void arttirRef(int &x)
{ // REFERENCE: Orijinal degisken
    x = x + 10;
    std::cout << "[Ref]    Fonksiyon icindeki x: " << x << std::endl;
}

void arttirPtr(int *p)
{ // POINTER: Adres uzerinden degistirir
    *p = *p + 10;
    std::cout << "[Ptr]    Fonksiyon icindeki *p: " << *p << std::endl;
}

int main()
{
    int sayi = 5;

    std::cout << "Baslangic sayi: " << sayi << "\n\n";

    // 1) VALUE
    arttirValue(sayi);
    std::cout << "Value sonrasi sayi: " << sayi << "\n\n";

    // 2) REFERENCE
    arttirRef(sayi);
    std::cout << "Ref   sonrasi sayi: " << sayi << "\n\n";

    // 3) POINTER
    arttirPtr(&sayi);
    std::cout << "Ptr   sonrasi sayi: " << sayi << "\n\n";

    return 0;
}
