// %% DERS 1 — Hücre 1
// Konu: İlk C++ programı
// Amacımız: C++ nasıl başlar, ekrana nasıl yazar görmüş olacağız.

#include <iostream>
#include <string>

int main() {
    std::cout <<"C++ eğitimimdeki ilk gün" << std::endl;
    return 0 ;
}

//  ------------------------------------------- //

// %% DERS 1 — Hücre 2
// Konu: Temel veri tipleri
// int, double, bool, char, string deneyeceğiz.

int main() {
    int yas = 21;
    double sicaklik = 36.7;
    bool aktif = true;
    char seviye = 'A';
    std::string isim = "Egitim";

    std::cout << "Yas: " << yas << std::endl;
    std::cout << "Sicaklik: " << sicaklik << std::endl;
    std::cout << "Aktif mi: " << aktif << std::endl;
    std::cout << "Seviye: " << seviye << std::endl;
    return 0;
}

//  ------------------------------------------- //

// %% DERS 1 — Hücre 3
// Konu: Kullanıcıdan veri almak.
// std::cin ile giriş alıyoruz.

#include <iostream>

int main(){
    int sayı1 , sayı2;

    std::cout << "İki sayı gir" ;
    std::cin >> sayı1 >> sayı2;

    std::cout << "Toplam: " << sayı1 + sayı2 <<std::endl;
    return 0;
}

int main() {
    int hiz, hedef;

    std::cout << "Anlik hızı ve hedef hızı giriniz: ";
    std::cin >> hiz >> hedef;

    int fark = hedef - hiz;

    std::cout << "Hedefe kalan fark: " << fark << " km/s" << std::endl;

    return 0;
}

//  ------------------------------------------- //

// %% DERS 1 — Hücre 4
// İf , else ifadeleri

#include <iostream>

int main()
{
    int hız;
    std::cout <<"Anlık hızınız nedir ?" ;
    std::cin >> hız;

    if (hız > 90)
    {
        std::cout << "Uyarı : Hız limitine ulaştınız" << std::endl;
    }
    else
    {
        std::cout << "Limit içindesiniz" << std::endl;
    }
    return 0 ;
}

// %% DERS 1 — Hücre 4 - Mini Görev
#include <iostream>

int main() {
    int hiz;

    std::cout << "Anlik hizinizi girin (km/s): ";
    std::cin >> hiz;

    if (hiz > 90) {
        std::cout << "Uyari: Hiz limitini ASTINIZ!" << std::endl;
    }
    else if (hiz >= 85 && hiz <= 90) {
        std::cout << "Dikkat: Hiz limitine YAKLASIYORSUNUZ!" << std::endl;
    }
    else {
        std::cout << "Hiz normal sinirlarda." << std::endl;
    }

    return 0;
}

//  ------------------------------------------- //
// %% DERS 1 — Hücre 5 -  Fonksiyon Mantığı

// * Fonksiyon dediğin şey:

// * Tekrar eden kodu tek yere yazmak

// * Parametre almak

// * Bir değer döndürmek

// * Programı düzenli hale getirmek

// Fonksiyon C++’ın bel kemiğidir.

#include <iostream>

double ortalama(int a , int b)
{
    return ( a+b ) / 2.0;
}

int main()
{
    std::cout <<"10 ve 20 ortalaması = " << ortalama(10,20) << std::endl;
    return 0;
}

// %% DERS 1 — Hücre 5 (Mini Görev Çözümü)

#include <iostream>

// Üç hızın ortalamasını hesaplayan fonksiyon
double ortalamaHiz(int h1, int h2, int h3) {
    return (h1 + h2 + h3) / 3.0;
}

// En büyük hızı döndürmek için bir fonksiyon (bonus)
int maxHiz(int h1, int h2, int h3) {
    int max = h1;
    if (h2 > max) max = h2;
    if (h3 > max) max = h3;
    return max;
}

int main() {
    int h1, h2, h3;

    std::cout << "Uc farkli hiz degeri giriniz: ";
    std::cin >> h1 >> h2 >> h3;

    std::cout << "Ortalama hiz: " << ortalamaHiz(h1, h2, h3) << " km/s" << std::endl;
    std::cout << "En yuksek hiz: " << maxHiz(h1, h2, h3) << " km/s" << std::endl;

    return 0;
}

//  ------------------------------------------- //

// %% DERS 1 — Hücre 6 (Mini Telemetri Projesi v1)

#include <iostream>
#include <string>

int main() {
    std::string plaka;
    int hiz;
    double motor;

    std::cout << "Arac plakasi: ";
    std::cin >> plaka;

    std::cout << "Anlik hiz (km/s): ";
    std::cin >> hiz;

    std::cout << "Motor sicakligi (C): ";
    std::cin >> motor;

    std::cout << "\n--- TELEMETRI OZETI ---\n";
    std::cout << "Plaka: " << plaka << std::endl;
    std::cout << "Hiz: " << hiz << " km/s" << std::endl;
    std::cout << "Motor sicakligi: " << motor << " C" << std::endl;

    // Uyarilar
    if (hiz > 130) {
        std::cout << "UYARI: YUKSEK HIZ!!!" << std::endl;
    }
    else if (hiz > 90) {
        std::cout << "Uyari: Hiz limitini astiniz." << std::endl;
    }

    if (motor > 100) {
        std::cout << "UYARI: Motor SICAK!" << std::endl;
    }

    return 0;
}

//  ------------------------------------------- //

// %% DERS 1 — Hücre 7
// Konu: for döngüsü - temel

#include <iostream>

int main() {
    std::cout << "1'den 10'a kadar sayilar:\n";

    for (int i = 1; i < 11; i++) {
        std::cout << i << " ";
    }

    std::cout << std::endl;
    return 0;
}


// Mini görev:
// 1’den 20’ye kadar çift sayıları yazdır.

int main() {
    std::cout << "1'den 20'ye kadar cift sayilar:\n";

    for (int i = 1; i <= 20; i++) {
        if (i % 2 == 0) {
            std::cout << i << std::endl;
        }
    }

    return 0;
}

// Daha PRO versiyon:

int main() {
    std::cout << "1'den 20'ye kadar cift sayilar:\n";

    for (int i = 2; i <= 20; i += 2) {
        std::cout << i << '\n';
    }

    return 0;
}

//  ------------------------------------------- //

// %% DERS 1 — Hücre 8
// Konu: while döngüsü - geri sayım

#include <iostream>

int main()
{
    int sayac = 5;
    std::cout <<"Geri sayım";

    while (sayac>0)
    {
        std::cout << sayac << std::endl;
        sayac--;
    }
    std::cout <<"Basladi"<< std::endl;
    return 0;
}

#include <iostream>
int main() {
    int sayi;

    std::cout << "Geri sayim icin bir sayi giriniz: ";
    std::cin >> sayi;

    while (sayi > 0) {
        std::cout << sayi << std::endl;
        sayi--;
    }

    std::cout << "Bitti!" << std::endl;
    return 0;
}

//  ------------------------------------------- //

// % DERS 1 — Hücre 9: do-while Döngüsü (Kullanıcıya Tekrar Sorma)

// do-while, en az 1 kere çalışsın mantığıyla ilerler.

#include <iostream>

int main() {
    int sayi;
    char devam;

    do {
        std::cout << "Bir sayi giriniz: ";
        std::cin >> sayi;

        if (sayi > 0)
            std::cout << "Pozitif sayi\n";
        else if (sayi < 0)
            std::cout << "Negatif sayi\n";
        else
            std::cout << "Sifir\n";

        std::cout << "Tekrar girmek ister misiniz? (e/h): ";
        std::cin >> devam;

    } while (devam == 'e' || devam == 'E');

    std::cout << "Programdan cikiliyor..." << std::endl;
    return 0;
}


//  ------------------------------------------- //

// ½ DERS 1 — Hücre 10: Mini Menü + Telemetri v1.5

// Bu hücre, Bölüm 1’in büyük finali.
// Basit bir menü ile kullanıcıdan veri alıyor, telemetriyi yazdırıyoruz.

// %% DERS 1 — Hücre 10
#include <iostream>
#include <string>

int main() {
    std::string plaka = "BOS";
    int hiz = 0;
    double motor = 0.0;

    int secim = 0;

    do {
        std::cout << "\n=== TELEMETRI MENUSU ===\n";
        std::cout << "1) Arac bilgisi gir\n";
        std::cout << "2) Telemetri ozetini goster\n";
        std::cout << "3) Cikis\n";
        std::cout << "Secim: ";
        std::cin >> secim;

        if (secim == 1) {
            std::cout << "Plaka: ";
            std::cin >> plaka;

            std::cout << "Hiz (km/s): ";
            std::cin >> hiz;

            std::cout << "Motor sicakligi (C): ";
            std::cin >> motor;
        }
        else if (secim == 2) {

            if (plaka == "BOS") {
                std::cout << "Henuz arac bilgisi girilmedi.\n";
            } else {
                std::cout << "\n--- TELEMETRI OZETI ---\n";
                std::cout << "Plaka: " << plaka << std::endl;
                std::cout << "Hiz: " << hiz << " km/s" << std::endl;
                std::cout << "Motor: " << motor << " C" << std::endl;

                if (hiz > 130)
                    std::cout << "UYARI: YUKSEK HIZ!\n";
                else if (hiz > 90)
                    std::cout << "Uyari: Hiz limitini astiniz.\n";

                if (motor > 100)
                    std::cout << "UYARI: Motor SICAK!\n";
                else if (motor < 60)
                    std::cout << "Bilgi: Motor soguk.\n";
            }
        }
        else if (secim == 3) {
            std::cout << "Cikis yapiliyor...\n";
        }
        else {
            std::cout << "Gecersiz secim!\n";
        }

    } while (secim != 3);

    return 0;
}