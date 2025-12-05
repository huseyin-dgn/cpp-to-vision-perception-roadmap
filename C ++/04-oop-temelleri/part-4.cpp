// 📘 Ders 4 – Bölüm 1  - Class ve Object Temelleri

#include <iostream>
#include <string>

class Oyuncu
{
public:
    std::string isim;
    int can;
    int mermi;

    void durumYaz()
    {
        std::cout << "Oyuncu : " << isim
                  << "Can :" << can
                  << "Mermi :" << mermi
                  << std::endl;
    }
};

int main()
{
    Oyuncu p1;
    p1.isim = "Huso";
    p1.can = 100;
    p1.mermi = 30;

    p1.durumYaz();

    return 0;
}

// ********************-------------------------***********************------------------

// Ders 4 – Bölüm 2  --- Public / Private / Protected (Erişim Belirleyicileri)

#include <iostream>
#include <string>

class Oyuncu
{
public:
    std::string isim;

private:
    int Can;
    int Mermi;

public:
    void ayarla(int yeniCan, int yeniMermi)
    {
        Can = yeniCan;
        Mermi = yeniMermi;
    }

    void durumYaz()
    {
        std::cout << "Oyuncu: " << isim
                  << " | Can: " << Can
                  << " | Mermi: " << Mermi
                  << std::endl;
    }
};

int main()
{
    Oyuncu p1;

    p1.isim = "Cano"; // public → OK
    // p1.can = 100;      // private → HATA
    // p1.mermi = 30;     // private → HATA

    p1.ayarla(100, 30); // OK, çünkü ayarla() public
    p1.durumYaz();

    return 0;
}

// ********************-------------------------***********************------------------

// Ders 4 – Bölüm 3 → Constructor (Kurucu Fonksiyon)
// 🔥 En basit örnek

#include <iostream>
#include <string>

class Oyuncu3
{
public:
    std::string isim_3;
    int can_3;
    int mermi_3;

    Oyuncu3()
    {
        can_3 = 100;
        mermi_3 = 30;
        std::cout << "Oyuncu oluşturuldu \n";
    }

    void DurumYaz()
    {
        std::cout << isim_3 << "| Can : " << can_3
                  << "| Mermi : " << mermi_3 << "\n";
    }
};

int main()
{
    Oyuncu3 p3;
    p3.isim_3 = "Hyso";
    p3.DurumYaz();
}

// ⭐ Parametreli Constructor -- Nesneyi oluştururken direkt değer vermek istiyorsan:

class Oyuncu4
{
public:
    std::string isim_4;
    int can_4;
    int mermi_4;

    Oyuncu4(std::string ad, int c, int m)
    {
        isim_4 = ad;
        can_4 = c;
        mermi_4 = m;
    }
};

// Kullanım: Oyuncu p("Cano", 120, 50);

// ********************-------------------------***********************------------------

// 📌 Ders 4 – Bölüm 4 → Destructor (Yıkıcı Fonksiyon)

#include <iostream>

#include <iostream>

class Sayaç
{
private:
    int *deger; // heap'te tutulacak

public:
    // Constructor
    Sayaç(int baslangic)
    {
        std::cout << "Constructor: Sayaç olusturuluyor...\n";
        deger = new int(baslangic); // HEAP'te int açtık
    }

    void arttir()
    {
        (*deger)++;
    }

    void yaz() const
    {
        std::cout << "Sayaç degeri: " << *deger << "\n";
    }

    // Destructor
    ~Sayaç()
    {
        std::cout << "Destructor: Beéllek serbest birakiliyor...\n";
        delete deger; // HEAP'teki int'i siliyoruz
    }
};

int main()
{
    {
        Sayaç s(10); // constructor burada
        s.yaz();
        s.arttir();
        s.yaz();
    } // scope biter → destructor burada otomatik çalışır

    std::cout << "Main devam ediyor...\n";
    return 0;
}

// ********************-------------------------***********************------------------

// 🟦 this Pointer - ( Ders 4 – Bölüm 5 )

#include <iostream>

class Oyuncu
{
private:
    int can;
    int mermi;

public:
    // 1) Parametreyle class değişkeni aynı isimde → this zorunlu
    void ayarla(int can, int mermi)
    {
        this->can = can; // sol: class değişkeni, sağ: parametre
        this->mermi = mermi;
    }

    // 2) "this" olmadan ne olur?
    void ayarlaYanlis(int can, int mermi)
    {
        can = can;     // tamamen gereksiz, parametre kendi kendine atanıyor
        mermi = mermi; // class değişkenleri değişmiyor
    }

    // 3) this ile method chaining yapma
    Oyuncu &arttir()
    {
        this->can++; // "bu nesnenin" can değerini arttır
        this->mermi++;
        return *this; // .arttir().arttir() zinciri için
    }

    void yaz() const
    {
        std::cout << "Can: " << can << ", Mermi: " << mermi << "\n";
    }
};

int main()
{
    Oyuncu p;

    p.ayarla(100, 30);
    p.yaz(); // Can: 100, Mermi: 30

    p.ayarlaYanlis(200, 50);
    p.yaz(); // HÂLÂ Can: 100, Mermi: 30  (yanlış method hiçbir işe yaramadı)

    p.arttir().arttir().arttir(); // method chaining
    p.yaz();                      // Can: 103, Mermi: 33

    return 0;
}

// ********************-------------------------***********************------------------

// Ders 4 – Bölüm 6 → Method (Sınıf içi fonksiyonlar) & const Method
#include <iostream>

class Oyuncu
{
private:
    int can;

public:
    Oyuncu(int baslangicCan)
        : can(baslangicCan) {}

    // NESNEYİ DEĞİŞTİREN METHOD (non-const)
    void hasarAl(int miktar)
    {
        can -= miktar;
        if (can < 0)
            can = 0;
    }

    // SADECE OKUYAN METHOD (const)
    int getCan() const
    {
        return can; // sadece okuyor, değiştirmiyor
    }
};

// Dışarıda, const referans alan bir fonksiyon
void yazRapor(const Oyuncu &o)
{
    // sadece const method çağırabilir
    std::cout << "Rapor - Can: " << o.getCan() << "\n";
    // o.hasarAl(10); // HATA: const üstünden non-const method çağıramazsın
}

int main()
{
    Oyuncu p(100);

    p.hasarAl(30);                   // nesne değişti
    std::cout << p.getCan() << "\n"; // const method → sadece okur

    yazRapor(p); // dışarıdan sadece okuyabilen fonksiyon

    return 0;
}

// ********************-------------------------***********************------------------

// Ders 4 – Bölüm 7 → Encapsulation (Kapsülleme) – Getter & Setter

#include <iostream>

class Oyuncu
{
private:
    int can; // dışarıdan erişilemez

public:
    // SETTER → değeri değiştirmeye izin verir
    void setCan(int yeniCan)
    {
        if (yeniCan < 0)
            yeniCan = 0; // kontrol ekledik
        can = yeniCan;
    }

    // GETTER → değeri OKUMAYA izin verir
    int getCan() const
    {
        return can; // veri sadece okunuyor
    }
};

int main()
{
    Oyuncu p;

    p.setCan(100);           // kontrol bizde
    std::cout << p.getCan(); // 100

    p.setCan(-50);           // setter kontrol ettiği için 0 olur
    std::cout << p.getCan(); // 0
}
// ********************-------------------------***********************------------------

// 🟦 struct vs class ( Ders 4 – Bölüm 8 )

// struct → default: public
struct OyuncuStruct
{
    int can;   // public
    int mermi; // public
};

// class → default: private
class OyuncuClass
{
    int can;   // private
    int mermi; // private
public:
    void ayarla(int c, int m)
    {
        can = c;
        mermi = m;
    }
    void yaz() const
    {
        std::cout << "Can: " << can << ", Mermi: " << mermi << "\n";
    }
};

int main()
{
    OyuncuStruct s;
    s.can = 100; // ✅ direk erişebiliyorsun (public)
    s.mermi = 30;

    std::cout << s.can << " " << s.mermi << "\n";

    OyuncuClass c;
    // c.can = 100;      // ❌ hata: private
    c.ayarla(100, 30); // ✅ public method üzerinden ayar
    c.yaz();

    return 0;
}

// ********************-------------------------***********************------------------

// Ders 4 – Bölüm 9 → Nesne Yaşam Döngüsü (Object Lifetime)

#include <iostream>
#include <memory>

class Nesne
{
public:
    Nesne() { std::cout << "Dogdu\n"; }
    ~Nesne() { std::cout << "Oluyor...\n"; }
};

int main()
{
    {
        Nesne a; // STACK → dogdu → scope bitince oluyor
    }

    {
        Nesne *b = new Nesne(); // HEAP → dogdu
        delete b;               // manuel oluyor
    }

    {
        auto c = std::make_unique<Nesne>(); // HEAP + otomatik RAII
    } // burada otomatik oluyor

    return 0;
}

// ********************-------------------------***********************------------------

// , Ders 4 – Bölüm 10 → static Üyeler (static değişken & static method)
#include <iostream>

class SınıfAdi
{
public:
    // 1) STATIC DEĞİŞKEN (class-level, ortak)
    static int ortakSayac;

    // 2) NORMAL ÜYE DEĞİŞKEN (her nesnenin kendi değeri)
    int deger;

    // 3) Constructor
    SınıfAdi(int d)
        : deger(d)
    {
        ortakSayac++; // her nesne oluşunca artar
    }

    // 4) STATIC METHOD (nesnesiz çağrılır)
    static void ortakBilgiYaz()
    {
        std::cout << "Toplam nesne sayisi: " << ortakSayac << "\n";

        // std::cout << deger;  // ❌ HATA: non-static üyeye erişemez
    }

    // 5) Normal method (nesne üzerinden çağrılır)
    void yaz() const
    {
        std::cout << "Nesne degeri: " << deger << "\n";
    }
};

// 6) static değişkenin class dışındaki TANIMI
int SınıfAdi::ortakSayac = 0;

int main()
{
    SınıfAdi a(10);
    SınıfAdi b(20);

    a.yaz(); // nesne methodu
    b.yaz();

    SınıfAdi::ortakBilgiYaz(); // static method → sınıf üzerinden

    return 0;
}

// ********************-------------------------***********************------------------

// Ders 4 – Bölüm 11 → const Object (const nesneler)

#include <iostream>
class Oyuncu
{
private:
    int can;

public:
    Oyuncu(int c) : can(c) {}

    void vur()
    { // değiştirir
        can -= 10;
    }

    int getCan() const
    { // değiştirmez
        return can;
    }
};

int main()
{
    const Oyuncu p(100);

    // p.vur();       // ❌ HATA: const nesne, değiştirilemez
    std::cout << p.getCan(); // ✔ OK: const method
}

// ********************-------------------------***********************------------------
// Ders 4 – Bölüm 12 → friend (friend function & friend class)

#include <iostream>
#include <string>

class Araba
{
private:
    int hiz;
    int motorSicakligi;

public:
    Araba(int h, int s)
        : hiz(h), motorSicakligi(s) {}

    // 1) Belirli bir fonksiyona özel izin
    friend void yazDetay(const Araba &a);

    // 2) Bir sınıfa tam erişim izni
    friend class Polis;
};

// ---------------------------
// Friend Function
// ---------------------------
void yazDetay(const Araba &a)
{
    // Normalde private alanlara erişilemezdi ama friend olduğu için erişiyor
    std::cout << "[Friend Function] Hiz: " << a.hiz
              << " | Sicaklik: " << a.motorSicakligi << "\n";
}

// ---------------------------
// Friend Class
// ---------------------------
class Polis
{
public:
    void radar(const Araba &a)
    {
        std::cout << "[Friend Class] Aracin hizi: " << a.hiz << "\n";
    }

    void motorKontrol(const Araba &a)
    {
        std::cout << "[Friend Class] Motor sicakligi: "
                  << a.motorSicakligi << "\n";
    }
};

int main()
{
    Araba a(120, 95);
    Polis p;

    // Friend function çalışıyor:
    yazDetay(a);

    // Friend class tüm private verilere erişebilir:
    p.radar(a);
    p.motorKontrol(a);

    return 0;
}
