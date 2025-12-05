// Görev 3:
// 1) "kontrolGiris" fonksiyonu yaz:
//    - parametre: int x
//    - x < 0 ise: std::invalid_argument("x negatif olamaz") fırlat
//
// 2) "islemler" fonksiyonu yaz:
//    - parametre: int x
//    - içinde kontrolGiris(x) çağır
//    - x == 0 ise: std::runtime_error("x sifir olamaz") fırlat
//    - x > 100 ise: std::overflow_error("x cok buyuk") fırlat
//    - aksi halde: x * 2 döndür
//
// 3) main():
//    - kullanıcıdan x al
//    - islemler(x) çağrısını try içinde yap
//    - invalid_argument, runtime_error, overflow_error için ayrı ayrı catch
//    - en sonda genel std::exception catch
//    - her catch'te farklı mesaj yaz (hangi tipten geldiğini görelim)

#include <iostream>
#include <stdexcept>

int kontrolGiris(int x)
{
    if (x < 0)
    {
        throw std::invalid_argument("x negatif olamaz");
    }

    return x;
}

int islemler(int x)
{
    x = kontrolGiris(x);

    if (x == 0)
    {
        throw std::runtime_error("x sifir olamaz");
    }

    if (x > 100)
    {
        throw std::overflow_error("x cok buyuk");
    }

    return x * 2;
}

int main()
{
    int x;
    std::cout << "Deger girin : ";
    std::cin >> x;

    try
    {
        int sonuc = islemler(x);
        std::cout << "Sonuc : " << sonuc << "\n";
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "[invalid_argument] " << e.what() << '\n';
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "[runtime_error] " << e.what() << '\n';
    }
    catch (const std::overflow_error &e)
    {
        std::cerr << "[overflow_error] " << e.what() << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << "[genel exception] " << e.what() << '\n';
    }

    return 0;
}
