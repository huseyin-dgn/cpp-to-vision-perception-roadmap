#include <iostream>
#include <algorithm> // sort, count, find, reverse, swap, fill, binary_search
#include <numeric>   // accumulate, gcd, lcm
#include <cmath>     // abs (bazı derleyicilerde <cstdlib>), sqrt, pow, round
#include <string>    // std::string, std::to_string

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

    int arr[100]; // ana dizimiz
    int brr[100]; // diger isler icin kullanacagimiz ikinci dizi

    std::cout << n << " adet tamsayi gir:\n";
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }

    // ----------------------------------------------------
    // 1) Toplam, ortalama (accumulate + double bölüm)
    // ----------------------------------------------------
    int sum = std::accumulate(arr, arr + n, 0);
    double avg = sum / static_cast<double>(n);

    // ----------------------------------------------------
    // 2) Diziyi sirala (sort) ve min/max bul
    // ----------------------------------------------------
    std::sort(arr, arr + n);

    int min_val = arr[0];
    int max_val = arr[n - 1];

    // aralik = |max - min|, karekoku, max'in karesi
    int range = std::abs(max_val - min_val);
    double range_sqrt = std::sqrt(static_cast<double>(range));
    double max_square = std::pow(static_cast<double>(max_val), 2.0);

    // ----------------------------------------------------
    // 3) Kullaniciya bir x sor: kac kez geciyor, ilk index ne?
    //    (count + find + binary_search + mod)
    // ----------------------------------------------------
    int x;
    std::cout << "\nAnaliz icin bir sayi gir (x): ";
    std::cin >> x;

    // kac kez geciyor?
    int count_x = std::count(arr, arr + n, x);

    // dizide var mi? (binary_search icin sira lazimdi, zaten sort ettik)
    bool exists = std::binary_search(arr, arr + n, x);

    // ilk index (find)
    int *p = std::find(arr, arr + n, x);

    // x cift mi / tek mi?
    bool is_even = (x % 2 == 0);

    std::cout << "\n--- X Analizi ---\n";
    std::cout << "x = " << x << "\n";
    std::cout << "Dizide var mi?        : " << (exists ? "EVET" : "HAYIR") << "\n";
    std::cout << "Kac kez geciyor?      : " << count_x << "\n";
    if (p != arr + n)
    {
        int index = p - arr; // pointer aritmetigi
        std::cout << "Ilk goruldugu index  : " << index << "\n";
    }
    else
    {
        std::cout << "Bu sayi hic gecmiyor.\n";
    }
    std::cout << "Cift mi / Tek mi?     : " << (is_even ? "CIFT" : "TEK") << "\n";

    // ----------------------------------------------------
    // 4) EBOB / EKOK (gcd / lcm) - min ve max icin
    // ----------------------------------------------------
    int ebob = std::gcd(min_val, max_val);
    int ekok = std::lcm(min_val, max_val);

    // ----------------------------------------------------
    // 5) Diziyi ters cevir (reverse),
    //    sonra ilk ve son elemani yer degistir (swap)
    // ----------------------------------------------------
    std::reverse(arr, arr + n);

    if (n >= 2)
    {
        std::swap(arr[0], arr[n - 1]);
    }

    // ----------------------------------------------------
    // 6) brr dizisinin ilk n elemanini 0 yap (fill)
    // ----------------------------------------------------
    std::fill(brr, brr + n, 0);

    // ----------------------------------------------------
    // 7) Ortalama yuvarla (round), rapor stringi olustur (to_string)
    // ----------------------------------------------------
    double avg_rounded_d = std::round(avg);
    int avg_rounded = static_cast<int>(avg_rounded_d);

    std::string report = "Min=" + std::to_string(min_val) +
                         ", Max=" + std::to_string(max_val) +
                         ", Range=" + std::to_string(range) +
                         ", Ebob=" + std::to_string(ebob) +
                         ", Ekok=" + std::to_string(ekok);

    // ----------------------------------------------------
    // 8) Tum sonuclari yazdir
    // ----------------------------------------------------
    std::cout << "\n--- Dizi Istatistikleri ---\n";
    std::cout << "Toplam (accumulate)   : " << sum << "\n";
    std::cout << "Ortalama              : " << avg << "\n";
    std::cout << "Ortalama (round)      : " << avg_rounded << "\n";
    std::cout << "En kucuk (sort sonra) : " << min_val << "\n";
    std::cout << "En buyuk (sort sonra) : " << max_val << "\n";
    std::cout << "Aralik |max-min|      : " << range << "\n";
    std::cout << "Aralik karekoku       : " << range_sqrt << "\n";
    std::cout << "Max'in karesi (pow)   : " << max_square << "\n";
    std::cout << "EBOB(min,max)         : " << ebob << "\n";
    std::cout << "EKOK(min,max)         : " << ekok << "\n";

    std::cout << "\nDizi (reverse + swap sonrasi): ";
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    std::cout << "brr (fill ile 0 yapildi):     ";
    for (int i = 0; i < n; i++)
    {
        std::cout << brr[i] << " ";
    }
    std::cout << "\n";

    std::cout << "\nRapor stringi: " << report << "\n";

    return 0;
}
