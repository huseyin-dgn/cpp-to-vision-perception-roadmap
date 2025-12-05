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