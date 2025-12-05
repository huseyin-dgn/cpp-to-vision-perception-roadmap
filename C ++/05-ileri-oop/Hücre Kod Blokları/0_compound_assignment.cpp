#include <iostream>

class Vektor2D
{
public:
    int x;
    int y;

    Vektor2D(int x = 0, int y = 0)
        : x(x), y(y) {}

    // +=  (a += b)
    Vektor2D &operator+=(const Vektor2D &d)
    {
        x += d.x;
        y += d.y;
        return *this; // chaining için
    }

    // -=  (a -= b)
    Vektor2D &operator-=(const Vektor2D &d)
    {
        x -= d.x;
        y -= d.y;
        return *this;
    }

    // *=  (a *= 3)  → scalar çarpma
    Vektor2D &operator*=(int s)
    {
        x *= s;
        y *= s;
        return *this;
    }

    // ==  (a == b)
    bool operator==(const Vektor2D &d) const
    {
        return x == d.x && y == d.y;
    }

    // !=  (a != b)
    bool operator!=(const Vektor2D &d) const
    {
        return !(*this == d);
    }

    // <  (a < b)  → uzunluğa göre kıyas (x^2 + y^2)
    bool operator<(const Vektor2D &d) const
    {
        int len1 = x * x + y * y;
        int len2 = d.x * d.x + d.y * d.y;
        return len1 < len2;
    }

    // <=, >, >= diğerlerinden türetilebilir
    bool operator<=(const Vektor2D &d) const
    {
        return *this < d || *this == d;
    }

    bool operator>(const Vektor2D &d) const
    {
        return d < *this;
    }

    bool operator>=(const Vektor2D &d) const
    {
        return !(*this < d);
    }
};

int main()
{
    Vektor2D a(1, 2);
    Vektor2D b(3, 4);

    a += b; // a = (4, 6)
    a *= 2; // a = (8, 12)

    std::cout << "a: (" << a.x << ", " << a.y << ")\n";

    std::cout << "a == b ? " << (a == b) << "\n";
    std::cout << "a != b ? " << (a != b) << "\n";
    std::cout << "a <  b ? " << (a < b) << "\n";
    std::cout << "a <= b ? " << (a <= b) << "\n";
    std::cout << "a >  b ? " << (a > b) << "\n";
    std::cout << "a >= b ? " << (a >= b) << "\n";

    return 0;
}
