// %% DERS 3 – Bolum 4 (Void Pointer)
#include <iostream>

int main()
{
    int x = 42;
    double y = 3.14;

    void *p;

    // int'i tut
    p = &x;
    std::cout << "int degeri: " << *(int *)p << std::endl;

    // double'i tut
    p = &y;
    std::cout << "double degeri: " << *(double *)p << std::endl;

    return 0;
}

// ----- BİR ÖRNEK DAHA -----

// %% DERS 3 – Bolum 4 Mini Gorev (Void Pointer ile farkli turler)
#include <iostream>

int main()
{
    char c = 'A';
    int i = 123;
    float f = 4.5f;

    void *p; // tek pointer, herkesin adresini sırayla tutacak

    // 1) char
    p = &c;
    std::cout << "char degeri: " << *(char *)p << std::endl;

    // 2) int
    p = &i;
    std::cout << "int degeri: " << *(int *)p << std::endl;

    // 3) float
    p = &f;
    std::cout << "float degeri: " << *(float *)p << std::endl;

    return 0;
}
