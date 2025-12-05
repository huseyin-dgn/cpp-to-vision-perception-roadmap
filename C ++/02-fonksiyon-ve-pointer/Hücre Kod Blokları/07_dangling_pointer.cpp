// %% BÖLÜM 3 — Hücre 9 (Dangling Pointer): Dangling Pointer (Sallanan Pointer)

// (Boş pointer başka, geçersiz pointer başka.)

// NULL pointer → hiçbir şeyi göstermez (güvenli).
// Dangling pointer → artık var olmayan bir değişkeni gösterir (ölümcül).

// Aşağıya direkt Jupyter hücresi formatında kodu veriyorum:

#include <iostream>

int *olustur()
{
    int x = 10; // x sadece bu fonksiyon içinde yaşar (stack)
    return &x;  // ❌ Fonksiyon bitince x yok olacak!
}

int main()
{
    int *ptr = olustur(); // ptr artık "geçersiz bir adres" tutuyor

    std::cout << "ptr adresi: " << ptr << std::endl;

    // ❌ Çok tehlikeli: geçersiz adresteki değeri okumaya çalışıyoruz
    std::cout << "ptr degeri: " << *ptr << std::endl;

    return 0;
}