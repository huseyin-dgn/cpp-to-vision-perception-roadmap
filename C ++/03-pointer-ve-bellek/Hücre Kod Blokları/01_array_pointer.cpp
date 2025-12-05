// %% DERS 3 – Bölüm 2 (Array + Pointer İlişkisi)
#include <iostream>

int main()
{
    int dizi[5] = {10, 20, 30, 40, 50};

    int *p = dizi; // dizi == &dizi[0]

    std::cout << "dizi[0]  = " << dizi[0] << std::endl;
    std::cout << "*p       = " << *p << std::endl;
    std::cout << "p adresi = " << p << std::endl;
    std::cout << "&dizi[0] = " << &dizi[0] << std::endl;

    // pointer ile dizi dolasma
    std::cout << "\nPointer ile dizi elemanlari: ";
    for (int i = 0; i < 5; i++)
    {
        std::cout << *(p + i) << " ";
    }

    // pointer'in kendi artmasi
    std::cout << "\n\nPointer yurutme: ";
    for (int *ptr = dizi; ptr < dizi + 5; ptr++)
    {
        std::cout << *ptr << " ";
    }

    return 0;
}
