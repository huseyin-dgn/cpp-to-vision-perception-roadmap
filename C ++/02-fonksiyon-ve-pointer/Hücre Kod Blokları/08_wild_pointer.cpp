
// %% DERS 2 — Hücre 10 (Wild Pointer)
// Wild pointer: baslangic degeri verilmeyen pointer

#include <iostream>

int main()
{
    int *p;
    std::cout << "P'nin tuttuğu adres : " << p << std::endl;

    std::cout << "P'nin gösterdigi deger :" << *p << std::endl;
    return 0;
}
