#include "Vector.h"

int main() {
    Vector a(1, 2, 3);
    Vector b(4, 5, 6);

    Vector sum1 = a;
    sum1 += b;
    Vector sum2 = b;
    sum2 += a;

    std::cout << "Sprawdzenie przemienności dodawania wektorów:\n";
    sum1.print("a + b");
    sum2.print("b + a");

    Vector u(0, 3, 0);
    Vector v(5, 5, 0);

    float dot = u.dotProduct(v);
    float lenU = u.length();
    float lenV = v.length();

    float cosTheta = dot / (lenU * lenV);
    float angleRad = std::acos(cosTheta);
    float angleDeg = angleRad * 180.0f / M_PI;

    std::cout << "\nKąt między wektorami [0,3,0] i [5,5,0] wynosi: "
        << angleDeg << " stopni.\n";

    Vector p1(4, 5, 1);
    Vector p2(4, 1, 3);

    Vector cross = p1.cross(p2);
    std::cout << "\nWektor prostopadły do [4,5,1] i [4,1,3]:\n";
    cross.print("wynik");

    cross.normalize();
    std::cout << "\nTen sam wektor po normalizacji:\n";
    cross.print("znormalizowany");

    return 0;
}
