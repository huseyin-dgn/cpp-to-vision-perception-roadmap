/*
Görev 4 – Rethrow (Hata içeride yakalanacak, loglanacak, sonra yukarıya tekrar fırlatılacak)

1) temelIslem(int x) fonksiyonu:
   - x < 0 ise: std::invalid_argument("x negatif") fırlat
   - x == 0 ise: std::runtime_error("x sifir") fırlat
   - aksi halde: x * 10 döndür

2) araKatman(int x) fonksiyonu:
   - içinde temelIslem(x) çağrılacak
   - try bloğu içinde sar
   - catch(const std::exception& e) içinde:
        - Ekrana: "[araKatman] hata: <mesaj>" yaz
        - Daha sonra aynı exception'ı yeniden fırlatmak için "throw;" kullan

3) main():
   - kullanıcıdan x al
   - araKatman(x) çağrısını try içinde yap
   - aşağıdaki catch bloklarını sırayla yaz:
        a) catch(const std::invalid_argument& e)
        b) catch(const std::runtime_error& e)
        c) catch(const std::exception& e)
        d) catch(...)
   - Her catch içinde hangi türden yakalandığını gösteren farklı bir mesaj yaz
*/

/*
Görev 4 – Rethrow (Hata içeride yakalanacak, loglanacak, sonra yukarıya tekrar fırlatılacak)
*/

#include <iostream>
#include <stdexcept>

int temelIslem(int x)
{
    if (x < 0)
    {
        throw std::invalid_argument("x negatif");
    }

    if (x == 0)
    {
        throw std::runtime_error("x sifir");
    }

    return x * 10;
}

int araKatman(int x)
{
    try
    {
        int sonuc = temelIslem(x);
        std::cout << "[araKatman] temelIslem sonucu: " << sonuc << "\n";
        return sonuc;
    }
    catch (const std::exception &e)
    {
        std::cerr << "[araKatman] hata: " << e.what() << '\n';
        throw; // ayni exception'i yukari tekrar firlat
    }
}

int main()
{
    int x;
    std::cout << "x gir: ";
    std::cin >> x;

    try
    {
        int sonuc = araKatman(x);
        std::cout << "[main] Sonuc: " << sonuc << "\n";
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "[main] invalid_argument yakalandi: " << e.what() << "\n";
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "[main] runtime_error yakalandi: " << e.what() << "\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "[main] std::exception yakalandi: " << e.what() << "\n";
    }
    catch (...)
    {
        std::cerr << "[main] Türü bilinmeyen bir exception yakalandi.\n";
    }

    return 0;
}
