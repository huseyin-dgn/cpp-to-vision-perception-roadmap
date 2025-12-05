//  %% BÖLÜM 3 — Hücre 8 (NULL pointer, nullptr, güvenli kullanım)

// 📌 NULL Pointer, nullptr ve Pointer Güvenliği**

// Aşağıdaki kod tamamen “güvenli pointer” mantığını öğretiyor.

#include <iostream>

void yazdir(int *p)
{
    if (p == nullptr)
    {
        std::cout << "Pointer bos : (nullptr)" << std::endl;
        return;
    }

    std::cout << "Deger: " << *p << std::endl;
}

int main()
{
    int sayi = 42;
    int *ptr1 = &sayi;
    int *ptr2 = nullptr;

    yazdir(ptr1);
    yazdir(ptr2);

    return 0;
}