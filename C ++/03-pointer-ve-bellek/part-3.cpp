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

// ************-------------------**************---------------***********

// %% DERS 3 – Bölüm 2 (Array + Pointer İlişkisi)

#include <iostream>

int main()
{
    int dizi[5] = {10, 20, 30, 40, 50};

    int *p = dizi;

    std::cout << "Dizi[0] :" << dizi[0] << std::endl;
    std::cout << "*p : " << *p << std::endl;
    std::cout << "P adresi :" << p << std::endl;

    std::cout << "\n Pointer ile dizi elemanları :";

    for (int i = 0; i < 5; i++)
    {
        std::cout << *(p + i) << " ";
    }

    std::cout << "\n\nPointer Yurutme :";
    for (int *pr = dizi; pr < dizi; pr++)
    {
        std::cout << *pr << "";
    }
    return 0;
}

// ************-------------------**************---------------***********

// %% DERS 3 – Bölüm 3 (Fonksiyon Pointer'ı)

#include <iostream>

int topla(int a, int b)
{
    return a + b;
}

int carp(int a, int b)
{
    return a * b;
}

int main()
{
    int (*fp)(int, int);
    fp = topla;
    std::cout << "Topla(3,4) = " << fp(3, 4) << std::endl;

    fp = carp;
    std::cout << "Carp(3,4) = " << fp(3, 4) << std::endl;

    return 0;
}

// %% DERS 3 – Bolum 4 (Void Pointer)

#include <iostream>
int main()
{
    int x = 42;
    double y = 3.14;

    void *p;

    p = &x;

    std::cout << "İnt degeri :" << *(int *)p << std::endl;

    p = &y;
    std::cout << "double degeri" << *(double *)p << std::endl;

    return 0;
}

// ************-------------------**************---------------***********

// %% DERS 3 – Bolum 5 (Pointer & Struct)

#include <iostream>

struct Arac
{
    int hiz;
    float motorSicakligi;
    bool arizaVarMi;
};

int main()
{
    Arac a; // normal struct degiskeni
    a.hiz = 80;
    a.motorSicakligi = 95.3f;
    a.arizaVarMi = false;

    // struct pointer
    Arac *p = &a;

    std::cout << "Normal erisim: " << std::endl;
    std::cout << "Hiz: " << a.hiz << std::endl;
    std::cout << "Motor sicakligi: " << a.motorSicakligi << std::endl;
    std::cout << "Ariza: " << a.arizaVarMi << std::endl;

    std::cout << "\nPointer ile erisim (->): " << std::endl;
    std::cout << "Hiz: " << p->hiz << std::endl;
    std::cout << "Motor sicakligi: " << p->motorSicakligi << std::endl;
    std::cout << "Ariza: " << p->arizaVarMi << std::endl;

    // pointer uzerinden de degistirebiliriz:
    p->hiz = 120;
    p->arizaVarMi = true;

    std::cout << "\nGuncellenmis degerler:" << std::endl;
    std::cout << "Hiz: " << a.hiz << std::endl;
    std::cout << "Ariza: " << a.arizaVarMi << std::endl;

    return 0;
}

// ************-------------------**************---------------***********

// %% DERS 3 – Bolum 6 (Dynamic Memory - new/delete)
#include <iostream>

int main()
{
    // 1) Tek bir int heap'te oluştur
    int *p = new int; // heap'ten 4 byte aldık
    *p = 42;

    std::cout << "Heap'teki deger: " << *p << std::endl;

    // 2) Belleği geri ver
    delete p;
    p = nullptr; // güvenlik

    // 3) Dynamic array
    int *dizi = new int[3];
    dizi[0] = 10;
    dizi[1] = 20;
    dizi[2] = 30;

    std::cout << "Dynamic array: ";
    for (int i = 0; i < 3; i++)
    {
        std::cout << dizi[i] << " ";
    }

    delete[] dizi; // dynamic array silinir
    dizi = nullptr;

    return 0;
}

// ************-------------------**************---------------***********

// %% DERS 3 – Bolum 7 🚀 Smart Pointer’lar

#include <iostream>
#include <memory>

int main()
{
    auto p = std::make_unique<int>(10);
    std::cout << *p << "\n";

    auto s1 = std::make_shared<int>(20);
    auto s2 = s1;

    std::cout << "Refcount : " << s1.use_count() << "\n";

    return 0;
}

// ************-------------------**************---------------***********

// %% DERS 3 – Bolum 8 🧠 STACK & HEAP Farkı

#include <iostream>
#include <memory>

int main()
{
    int stackVal = 10;          // STACK
    int *heapVal = new int(20); // HEAP

    std::unique_ptr<int> smart = std::make_unique<int>(30); // HEAP ama auto-delete

    std::cout << "stack: " << stackVal << "\n";
    std::cout << "heap: " << *heapVal << "\n";
    std::cout << "smart: " << *smart << "\n";

    delete heapVal; // HEAP temizliği
    heapVal = nullptr;

    return 0;
}
