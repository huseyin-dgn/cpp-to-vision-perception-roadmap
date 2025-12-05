// #include <iostream>
// #include <memory>

// int main()
// {
//     auto p = std::make_unique<int>(10);
//     std::cout << *p << "\n";

//     auto s1 = std::make_shared<int>(20);
//     auto s2 = s1;

//     std::cout << "Refcount : " << s1.use_count() << "\n";

//     return 0;
// }

/// ------- BAŞKA BİR ÖRNEK ----------- ///

#include <iostream>
#include <memory> // smart pointer'lar burada

int main()
{
    // 1) unique_ptr  - tek sahip
    std::unique_ptr<int> u = std::make_unique<int>(10);
    std::cout << "unique_ptr degeri: " << *u << "\n";

    // Sahipligi tasima (move)
    std::unique_ptr<int> u2 = std::move(u);
    if (!u)
    {
        std::cout << "u artik bos (sahiplik u2'ye gecti)\n";
    }
    std::cout << "u2 degeri: " << *u2 << "\n";

    // 2) shared_ptr  - ortak sahiplik
    std::shared_ptr<int> s1 = std::make_shared<int>(20);
    std::shared_ptr<int> s2 = s1; // kopyaladık, artik 2 sahip var

    std::cout << "shared_ptr degeri: " << *s1 << "\n";
    std::cout << "use_count: " << s1.use_count() << "\n"; // kac sahip var?

    // 3) weak_ptr  - sahip degil, uzaktan bakiyor
    std::weak_ptr<int> w = s1; // s1/s2'nin tuttugu yere zayif isaretci

    if (auto locked = w.lock())
    { // weak_ptr -> shared_ptr dene
        std::cout << "weak_ptr hala gecerli, deger: " << *locked << "\n";
    }

    // shared_ptr'lari sifirlayalim
    s1.reset();
    s2.reset(); // artik hic shared_ptr kalmadi, int silindi

    if (auto locked = w.lock())
    {
        std::cout << "Hala var (bu satir normalde calismaz)\n";
    }
    else
    {
        std::cout << "weak_ptr artik BOS (nesne silinmis)\n";
    }

    return 0;
}
