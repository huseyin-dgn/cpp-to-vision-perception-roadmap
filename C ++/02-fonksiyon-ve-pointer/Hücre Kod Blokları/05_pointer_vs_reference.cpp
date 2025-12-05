// // %% BÖLÜM 3 — Hücre 7 (Pointer vs Reference)

// 📌 Pointer vs Reference — Aynı işi nasıl farklı yaparlar?**

// Aşağıdaki kod, ikisinin farkını gözünün içine sokan en temiz örnek.

#include <iostream>

void changewithReference(int &r)
{
    r = r + 10;
}

void changewithpointer(int *p)
{
    *p = *p + 10;
}

int main()
{
    int sayı = 5;

    changewithpointer(&sayı);
    std::cout << "Pointer sonrası sayi :" << sayı << std::endl;

    changewithReference(sayı);
    std::cout << "Reference sonrası : " << sayı << std::endl;

    return 0;
}