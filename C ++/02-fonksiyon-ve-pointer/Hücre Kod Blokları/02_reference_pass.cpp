// %% DERS 2 — Hücre 4 (Reference Pass)
// 📌 Reference Pass (&) — Orijinal Değişkenle Çalışmak**

// C++’ın en önemli noktası burası:
// Fonksiyona bir değişkeni & (referans) ile verirsen, artık fotokopi değil, gerçek orijinale dokunursun.

#include <iostream>

void increaseByRef(int &x)
{
    std::cout << "Fonksiyon baslangic x: " << x << std::endl;

    x = x + 10; // ORIJINAL degisiyor

    std::cout << "Fonksiyon sonunda x: " << x << std::endl;
}

int main()
{
    int sayi = 5;

    std::cout << "Main - Once sayi: " << sayi << std::endl;

    increaseByRef(sayi); // sayi'nin kendisi gider

    std::cout << "Main - Sonra sayi: " << sayi << std::endl;

    return 0;
}
