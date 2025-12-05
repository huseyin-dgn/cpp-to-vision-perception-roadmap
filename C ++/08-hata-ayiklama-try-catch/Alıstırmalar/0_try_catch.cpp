// Görev 1:
// Aşağıdaki bol() fonksiyonu b=0 olduğunda hata fırlatmalı.
// main() içinde bu hatayı try–catch ile yakalayıp
// ekrana "Hata: ..." şeklinde düzgün bir mesaj yazmalısın.

#include <iostream>

int bol(int a, int b)
{
    if (b == 0)
    {
        throw std::runtime_error("Sıfıra bolme hatası");
    }
    return a / b;
}

int main()
{
    try
    {
        int sonuc = bol(10, 0);
        std::cout << "Sonuc :" << sonuc << "\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Hata yakalandı :" << e.what() << "\n";
    }

    return 0;
}