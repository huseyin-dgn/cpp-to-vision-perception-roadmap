// Görev 2:
// 1) hesapla(int a, int b) fonksiyonu yaz:
//    - a < 0 ise: std::invalid_argument fırlat ("a negatif olamaz")
//    - b == 0 ise: std::runtime_error fırlat ("b sıfır olamaz")
//    - aksi halde: a / b sonucunu döndür
//
// 2) main() içinde:
//    - kullanıcıdan a ve b al
//    - hesapla(a, b) çağrısını try içinde yap
//    - invalid_argument için ayrı catch
//      runtime_error için ayrı catch
//      diğer tüm exception'lar için genel catch yaz
//
// Amaç: farklı hata tiplerini farklı şekilde yönetmeyi öğrenmek.

#include <iostream>
#include <stdexcept>

int hesapla(int a, int b)
{
    if (a < 0)
    {
        throw std::invalid_argument("a negatif olamaz");
    }

    if (b == 0)
    {
        throw std::runtime_error("b sıfır olamaz");
    }

    return a / b;
}

int main()
{
    int a, b;
    std::cout << "a ve b degerlerini gir: ";
    std::cin >> a >> b;

    try
    {
        int sonuc = hesapla(a, b);
        std::cout << "Sonuç: " << sonuc << "\n";
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Geçersiz argüman hatası: " << e.what() << '\n';
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Çalışma zamanı hatası: " << e.what() << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << "Genel hata: " << e.what() << '\n';
    }

    return 0;
}
