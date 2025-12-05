// 🔹 Soru B – Dizideki Tekil (Bir Kere Geçen) Eleman
//
// int find_unique(const int* arr, std::size_t n);
//
// - Tüm elemanlar 2 kez geçiyor
// - Sadece 1 tane eleman tam 1 kez geçiyor
//   ör: [2, 3, 2, 5, 5] → sonuç = 3
//
// - Çözüm 1: Frekans sayma (O(n))
// - Çözüm 2: XOR hilesi (O(n), O(1) bellek)

#include <iostream>
#include <cstddef>

int find_unique(const int *arr, std::size_t n)
{
    int result = 0;

    for (std::size_t i = 0; i < n; i++)
    {
        result ^= arr[i];
    }
    return result;
}

// 🔥 XOR (^) Operatörü – Bu Soru İçin Tanım

// XOR (exclusive OR) iki sayının bitlerine bakar ve
// bitler FARKLI ise 1, aynı ise 0 üretir.

// Yani:

// 0 ^ 0 = 0
// 1 ^ 1 = 0
// 0 ^ 1 = 1
// 1 ^ 0 = 1

// Bu özellikten şu üç sonuç çıkar (problem için çok kritik):

// 1) Aynı sayı XOR’lanırsa sıfır olur
// x ^ x = 0

// Bu yüzden dizide iki kez geçen her eleman birbirini yok eder.

// 2) Sıfır ile XOR sonuç değişmez
// x ^ 0 = x

// Yani başlangıçta result = 0 yapmak güvenlidir.

// 3) XOR işleminin sırası önemli değildir
// a ^ b ^ a == b

// Yani dizide tekrar eden elemanlar nerede olursa olsun
// çift olanlar yok olur, tek kalan direkt ortaya çıkar.

// 🔥 Bu problemin özel XOR mantığı

// Verilen dizide:

// Tüm elemanlar 2 kez geçer.

// Sadece bir eleman 1 kez geçer.

// Dizinin tamamını XOR’larsan:

// Çift geçenler → x ^ x = 0 ile sıfırlanır.

// Geriye sadece tek geçen eleman kalır.

// Bu yüzden çözüm tek satırdır:

// result ^= arr[i];

// XOR, aynı sayıları birbirine çarparak yok eden bir operatördür.
// Bir dizi içinde bütün elemanlar iki kez geçiyor ve bir tanesi bir kez geçiyorsa,
// tüm diziyi XOR’lamak tek geçen elemanı verir.

// EĞER NORMAL ALGORİTMA İLE ÇÖZMEK İSTENİRSE //

int find_unique_bruteforce(const int *arr, std::size_t n)
{
    for (std::size_t i = 0; i < n; ++i)
    {
        int count = 0;

        for (std::size_t j = 0; j < n; ++j)
        {
            if (arr[j] == arr[i])
            {
                count++;
            }
        }

        if (count == 1)
        {
            return arr[i]; // tek geçen elemanı bulduk
        }
    }

    return -1; // yoksa
}
