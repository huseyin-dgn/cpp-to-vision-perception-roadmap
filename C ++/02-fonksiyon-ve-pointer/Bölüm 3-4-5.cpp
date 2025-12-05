#include <iostream>
#include <string>

void value(std::string msg)
{ // KOPYA
    std::cout << "value:  " << &msg << std::endl;
}

void ref(std::string &msg)
{ // ORIJINAL
    std::cout << "ref:    " << &msg << std::endl;
}

void cref(const std::string &msg)
{ // ORIJINAL + KILIT
    std::cout << "cref:   " << &msg << std::endl;
}

int main()
{
    std::string mesaj = "selam";
    std::cout << "main:   " << &mesaj << std::endl;

    value(mesaj);
    ref(mesaj);
    cref(mesaj);

    return 0;
}
