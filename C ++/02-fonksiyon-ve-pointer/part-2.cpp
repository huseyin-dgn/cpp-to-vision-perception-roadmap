// %% DERS 2 — Hücre 1: Menü Gösteren Fonksiyon (menuGoster)

// Bu hücrede:

// * Menü metnini yazdıran,

// * Kullanıcıdan seçim isteyen,

// * Seçimi geri döndüren tek bir fonksiyon yazıyoruz.

// * Bu fonksiyon ileride sürekli çağırılacak, yani güzel bir temel olacak.

// %% DERS 2 — Hücre 1 (cin’siz test)
#include <iostream>

int menuGoster()
{
    std::cout << "\n=== TELEMETRI MENU ===\n";
    std::cout << "1) Arac bilgisi gir\n";
    std::cout << "2) Telemetri ozetini goster\n";
    std::cout << "3) Cikis\n";
    std::cout << "Secim: ";

    int secim = 2; // simdilik elle atiyoruz
    std::cout << secim << std::endl;
    return secim;
}

int main()
{
    int s = menuGoster();
    std::cout << "Secilen menu: " << s << std::endl;
    return 0;
}

// -------------------------------------------------------------------//

// %% DERS 2 — Hücre 2
// Amaç: Araç bilgisi almayı da fonksiyona taşımak

// Şimdi yeni bir fonksiyon daha yazacağız:

// aracBilgisiGir

// Plaka, hız ve motor sıcaklığını kullanıcıdan alacak

// Bu değerleri dışarıya geri yazacak

// Bunu yapmanın en temiz yolu: referans parametre (&) kullanmak.

#include <iostream>
#include <string>

void AracBilgisiGir(std::string &plaka, int &hiz, double &motorSicakligi)
{
    std::cout << "Plaka :";
    std::cin >> plaka;

    std::cout << "Hiz (km/s) :";
    std::cin >> hiz;

    std::cout << "Motor Sicakligi (C) :";
    std::cin >> motorSicakligi;
}

int main()
{
    std::string plaka;
    int hiz = 0;
    double motor = 0.0;

    std::cout << "Arac bilgisi giris fonksiyonu test ediliyor...\n";

    AracBilgisiGir(plaka, hiz, motor);

    std::cout << "\n--- GIRDIGINIZ BILGILER ---\n";
    std::cout << "Plaka: " << plaka << std::endl;
    std::cout << "Hiz: " << hiz << " km/s" << std::endl;
    std::cout << "Motor sicakligi: " << motor << " C" << std::endl;

    return 0;
}

// -------------------------------------------------------------------//

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
// -------------------------------------------------------------------//

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

// -------------------------------------------------------------------//

// %% Ders 2 — Hücre 5 (Const Reference)

#include <iostream>
#include <string>

void printText(const std::string &text)
{
    std::cout << "Gelen Metin : " << text << std::endl;
}

int main()
{
    std::string mesaj = "Arac telemetri sistemi aktif.";
    printText(mesaj);

    std::cout << "Maindeki mesaj : " << mesaj << std::endl;
    return 0;
}

// -------------------------------------------------------------------//

// %% Ders 2 — Hücre 6 (Pointer'a Giriş)

// 📌 Pointer’a İlk Adım (Bellek adresi → Pointer → Değişkene erişim)**

// Pointer dediğin şey aslında SÜPER BASİT:

// Pointer = bir değişkenin RAM’deki adresini tutan değişkendir.
// Yani “adres defteri”.

// Bir pointer aslında sadece şunu saklar:

// Şu değişken nerede duruyor? (adres)

// O adrese nasıl giderim? (→ operatörü)

// Bunu göstermek için en sade, sıfır karışıklık örneği geliyor.

#include <iostream>

int main()
{
    int sayı = 42;
    int *ptr = &sayı;

    std::cout << "Sayi degeri:" << sayı << std::endl;
    std::cout << "Sayı adresi:" << &sayı << std::endl;

    std::cout << "ptr içindeki sayı:" << ptr << std::endl;
    std::cout << "ptr'nin gösterdiği adres: " << *ptr << std::endl;

    return 0;
}

// -------------------------------------------------------------------//

// // %% BÖLÜM 3 — Hücre 7 (Pointer vs Reference)

// 📌 Pointer vs Reference — Aynı işi nasıl farklı yaparlar?**

// Aşağıdaki kod, ikisinin farkını gözünün içine sokan en temiz örnek.

#include <iostream>

void changewithReference(int &r)
{
    r = r + 10;
}

void changewithpointer(int *p)
{
    *p = *p + 10;
}

int main()
{
    int sayı = 5;

    changewithpointer(&sayı);
    std::cout << "Pointer sonrası sayi :" << sayı << std::endl;

    changewithReference(sayı);
    std::cout << "Reference sonrası : " << sayı << std::endl;

    return 0;
}

// -------------------------------------------------------------------//

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

// -------------------------------------------------------------------//

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

// -------------------------------------------------------------------//

// %% DERS 2 — Hücre 10 (Wild Pointer)
// Wild pointer: baslangic degeri verilmeyen pointer

#include <iostream>

int main()
{
    int *p;
    std::cout << "P'nin tuttuğu adres : " << p << std::endl;

    std::cout << "P'nin gösterdigi deger :" << *p << std::endl;
    return 0;
}

// -------------------------------------------------------------------//

// %% DERS 2 — Hücre 11 (Value vs Reference vs Pointer Kıyas Kodu)

// %% DERS 2 — Hücre 11 (Value vs Reference vs Pointer Kıyas Kodu)

#include <iostream>

void arttirValue(int x)
{ // VALUE: Kopya ile çalışır
    x = x + 10;
    std::cout << "[Value]  Fonksiyon icindeki x: " << x << std::endl;
}

void arttirRef(int &x)
{ // REFERENCE: Orijinal degisken
    x = x + 10;
    std::cout << "[Ref]    Fonksiyon icindeki x: " << x << std::endl;
}

void arttirPtr(int *p)
{ // POINTER: Adres uzerinden degistirir
    *p = *p + 10;
    std::cout << "[Ptr]    Fonksiyon icindeki *p: " << *p << std::endl;
}

int main()
{
    int sayi = 5;

    std::cout << "Baslangic sayi: " << sayi << "\n\n";

    // 1) VALUE
    arttirValue(sayi);
    std::cout << "Value sonrasi sayi: " << sayi << "\n\n";

    // 2) REFERENCE
    arttirRef(sayi);
    std::cout << "Ref   sonrasi sayi: " << sayi << "\n\n";

    // 3) POINTER
    arttirPtr(&sayi);
    std::cout << "Ptr   sonrasi sayi: " << sayi << "\n\n";

    return 0;
}
