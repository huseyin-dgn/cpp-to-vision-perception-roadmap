// %%   DERS 2 — Hücre 3: Value vs Reference (Değer – Referans)
// Bu ders C++’ın gerçek mantığını açacak. Bundan sonra pointerlar bile sana çok kolay gelecek.

// ----- Bu hücrede göreceğin şey:
// ----- Fonksiyona değişken verirsen, aslında onun KOPYASI gider.
// ----- Yani fonksiyon içindeki değişiklik dışarıyı etkilemez.

#include <iostream>

void arttırValue(int x)
{
    x = x + 10;
    std::cout << "Fonksiyon içindeki x:" << x << std::endl;
}

int main()
{
    int sayı = 5;

    std::cout << "Fonksiyon cagrilmadan once sayi :" << sayı << std::endl;
    arttırValue(sayı);
    std::cout << "Fonksiyon cagrildiktan sonra sayi:" << sayı << std::endl;
    return 0;
}