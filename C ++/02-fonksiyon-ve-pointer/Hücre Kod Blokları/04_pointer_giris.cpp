// %% Ders 2 — Hücre 6 (Pointer'a Giriş)

// 📌 Pointer’a İlk Adım (Bellek adresi → Pointer → Değişkene erişim)**

// Pointer dediğin şey aslında SÜPER BASİT:

// Pointer = bir değişkenin RAM’deki adresini tutan değişkendir.
// Yani “adres defteri”.

// Bir pointer aslında sadece şunu saklar:

// Şu değişken nerede duruyor? (adres)

// O adrese nasıl giderim? (→ operatörü)

// Bunu göstermek için en sade, sıfır karışıklık örneği geliyor.

#include <iostream>

int main()
{
    int sayı = 42;
    int *ptr = &sayı;

    std::cout << "Sayi degeri:" << sayı << std::endl;
    std::cout << "Sayı adresi:" << &sayı << std::endl;

    std::cout << "ptr içindeki sayı:" << ptr << std::endl;
    std::cout << "ptr'nin gösterdiği adres: " << *ptr << std::endl;

    return 0;
}
