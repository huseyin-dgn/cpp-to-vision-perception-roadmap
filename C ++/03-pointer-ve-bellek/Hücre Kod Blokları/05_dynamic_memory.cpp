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

// %% DERS 3 – Bolum 6 Mini Gorev (Dynamic Memory)

#include <iostream>

int main()
{
    // 1) Tek bir double heap'te olustur
    double *ptr = new double; // heap'ten alan aldik
    *ptr = 3.1415;            // degeri ata

    std::cout << "Heap'teki double degeri: " << *ptr << std::endl;

    // 2) Belleği geri ver
    delete ptr;
    ptr = nullptr; // guvenlik icin sifirla

    // 3) Dynamic array olustur
    float *sensorData = new float[4];

    sensorData[0] = 10.5f;
    sensorData[1] = 20.2f;
    sensorData[2] = 30.8f;
    sensorData[3] = 40.1f;

    std::cout << "Sensor verileri: ";
    for (int i = 0; i < 4; i++)
    {
        std::cout << sensorData[i] << " ";
    }
    std::cout << std::endl;

    // 4) Belleği geri ver
    delete[] sensorData;
    sensorData = nullptr;

    return 0;
}
