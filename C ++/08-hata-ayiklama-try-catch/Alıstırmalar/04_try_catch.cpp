/*
Görev 5 – Model Yükleme Senaryosu (Simülasyon)

1) kontrolModelYolu(const std::string& path)
   - path boşsa: std::invalid_argument("model yolu bos") fırlat
   - path ".pt" ile bitmiyorsa: std::runtime_error("TorchScript dosyasi degil") fırlat
   - aksi halde: path'i geri döndür

2) modelYukle(const std::string& path)
   - try bloğu içinde kontrolModelYolu(path) çağır
   - eğer exception gelmezse:
        - ekrana: "[modelYukle] Model basariyla yuklendi: <path>"
        - true döndür
   - eğer exception yakalanırsa:
        - "[modelYukle] Hata: <mesaj>" yaz
        - ayni exception'i "throw;" ile tekrar yukari fırlat

3) uygulamayiCalistir()
   - sabit bir string tanımla: std::string modelPath = "model.pt";  (veya test etmek için bilerek "model.onnx" yapabilirsin)
   - modelYukle(modelPath) çağır
   - ekrana: "[uygulamayiCalistir] Uygulama normal sekilde devam ediyor" yaz

4) main()
   - uygulamayiCalistir() çağrısını try içinde yap
   - aşağıdaki sırayla catch blokları yaz:
        a) std::invalid_argument
        b) std::runtime_error
        c) std::exception
        d) catch(...)
   - Her catch içinde, hangi türü yakaladığını belli eden bir mesaj yaz
*/

#include <iostream>
#include <stdexcept>

// 1) Model yolu kontrol fonksiyonu
std::string kontrolModelYolu(const std::string &path)
{
    if (path.empty())
    {
        throw std::invalid_argument("model yolu bos");
    }

    // Çok basit bir kontrol: string ".pt" ile bitiyor mu?
    if (path.size() < 3 || path.substr(path.size() - 3) != ".pt")
    {
        throw std::runtime_error("TorchScript dosyasi degil (uzanti .pt degil)");
    }

    return path;
}

// 2) Model yükleme fonksiyonu (ara katman)
bool modelYukle(const std::string &path)
{
    try
    {
        std::string dogrulanmisYol = kontrolModelYolu(path);
        std::cout << "[modelYukle] Model basariyla yuklendi: " << dogrulanmisYol << "\n";
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "[modelYukle] Hata: " << e.what() << "\n";
        throw; // Aynı exception'ı bir üst seviyeye fırlat
    }
}

// 3) Uygulamanın ana işlevi
void uygulamayiCalistir()
{
    // Burayı istersen farklı değerle dene:
    // std::string modelPath = "";              // invalid_argument atar
    // std::string modelPath = "model.onnx";    // runtime_error atar
    std::string modelPath = "model.pt"; // başarılı senaryo

    bool ok = modelYukle(modelPath);
    if (ok)
    {
        std::cout << "[uygulamayiCalistir] Uygulama normal sekilde devam ediyor.\n";
    }
}

// 4) En dış seviye: main
int main()
{
    try
    {
        uygulamayiCalistir();
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

    std::cout << "[main] Program temiz sekilde sonlandi.\n";
    return 0;
}
