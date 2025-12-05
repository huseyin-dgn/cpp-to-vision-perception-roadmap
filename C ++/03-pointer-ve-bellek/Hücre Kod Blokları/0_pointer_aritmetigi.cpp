// %% DERS 3 – Bölüm 1 (Pointer Arithmetic)
#include <iostream>

int main()
{
    int dizi[5] = {10, 20, 30, 40, 50};

    int *p = dizi; // dizi -> ilk elemanın adresi

    std::cout << "Ilk eleman: " << *p << std::endl;

    p++; // bir sonraki elemana git
    std::cout << "p++ sonrasi: " << *p << std::endl;

    p++; // tekrar ilerle
    std::cout << "p tekrar ilerledi: " << *p << std::endl;

    // pointer ile dizi gezmek
    p = dizi; // basa don
    std::cout << "\nTum elemanlar: ";
    for (int i = 0; i < 5; i++)
    {
        std::cout << *(p + i) << " ";
    }

    std::cout << std::endl;
    return 0;
}
