// 🔹 Soru  – Dizide toplam, ortalama, pozitif/negatif sayisi
//
// Kurallar:
//  - Sadece int ve C tarzı dizi kullan (vector yok).
//  - Toplam ve ortalama için for döngüsü kullan.
//
// Görev:
//  - Kullanıcıdan n al (1–100 arasi).
//  - n tane tamsayi oku, arr[] dizisine doldur.
//  - Dizinin:
//      * Toplamini hesapla
//      * Ortalama degerini (double olarak) hesapla
//      * Pozitif sayi adedini bul
//      * Negatif sayi adedini bul
//      * Sifir sayisini bul
//  - Sonuclari ekrana yazdir.

// 🔹 Soru 1 – Dizide toplam, ortalama, pozitif/negatif sayisi
//
// Kurallar:
//  - Sadece int ve C tarzı dizi kullan (vector yok).
//  - Toplam ve ortalama için for döngüsü kullan.
//
// Görev:
//  - Kullanıcıdan n al (1–100 arasi).
//  - n tane tamsayi oku, arr[] dizisine doldur.
//  - Dizinin:
//      * Toplamini hesapla
//      * Ortalama degerini (double olarak) hesapla
//      * Pozitif sayi adedini bul
//      * Negatif sayi adedini bul
//      * Sifir sayisini bul
//  - Sonuclari ekrana yazdir.

#include <iostream>

int main()
{
    int n;
    std::cout << "Kac eleman gireceksin? ";
    std::cin >> n;

    if (n <= 0 || n > 100)
    {
        std::cout << "n 1 ile 100 arasinda olmali.\n";
        return 1;
    }

    int arr[100];

    std::cout << n << " adet tamsayi gir:\n";
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }

    int sum = 0;
    int positive_count = 0;
    int negative_count = 0;
    int zero_count = 0;

    for (int i = 0; i < n; i++)
    {
        int x = arr[i];

        sum += x;

        if (x > 0)
        {
            positive_count++;
        }
        else if (x < 0)
        {
            negative_count++;
        }
        else
        {
            zero_count++;
        }
    }

    double avg = sum / 3.0; // DİKKAT: BU BİLEREK HATALI YAZILDI

    double avg_1 = sum / static_cast<double>(n); // DOĞRU YAZIM ŞEKLİ BU ŞEKİLDEDİR.

    std::cout << "Toplam        : " << sum << "\n";
    std::cout << "Ortalama      : " << avg_1 << "\n";
    std::cout << "Pozitif sayi  : " << positive_count << "\n";
    std::cout << "Negatif sayi  : " << negative_count << "\n";
    std::cout << "Sifir sayisi  : " << zero_count << "\n";

    return 0;
}
