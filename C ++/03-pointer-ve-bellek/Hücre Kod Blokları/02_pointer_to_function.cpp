// %% DERS 3 – Bölüm 3 (Fonksiyon Pointer'ı)

#include <iostream>

int topla(int a, int b)
{
    return a + b;
}

int carp(int a, int b)
{
    return a * b;
}

int main()
{
    int (*fp)(int, int);
    fp = topla;
    std::cout << "Topla(3,4) = " << fp(3, 4) << std::endl;

    fp = carp;
    std::cout << "Carp(3,4) = " << fp(3, 4) << std::endl;

    return 0;
}

// ----- BİR ÖRNEK DAHA ----

// %% DERS 3 – Bolum 3 Mini Gorev (Fonksiyon Pointer ile Hesap Makinesi)
#include <iostream>

int Topla(int a, int b)
{
    return a + b;
}

int cikar(int a, int b)
{
    return a - b;
}

int bol(int a, int b)
{
    if (b == 0)
    {
        std::cout << "0'a bolme hatasi!" << std::endl;
        return 0;
    }
    return a / b;
}

int main()
{
    int a, b;
    int secim;

    std::cout << "Iki sayi girin: ";
    std::cin >> a >> b;

    std::cout << "Islem secin:\n";
    std::cout << "1) Topla\n";
    std::cout << "2) Cikar\n";
    std::cout << "3) Bol\n";
    std::cout << "Secim: ";
    std::cin >> secim;

    // Fonksiyon pointer tanimi
    int (*fp)(int, int) = nullptr;

    if (secim == 1)
    {
        fp = Topla;
    }
    else if (secim == 2)
    {
        fp = cikar;
    }
    else if (secim == 3)
    {
        fp = bol;
    }
    else
    {
        std::cout << "Gecersiz secim!" << std::endl;
        return 0;
    }

    // Pointer uzerinden fonksiyon cagir
    int sonuc = fp(a, b);
    std::cout << "Sonuc: " << sonuc << std::endl;

    return 0;
}
