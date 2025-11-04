#include "Matrix4x4.h"
#include "Vector4.h"
#include "Vector3.h"
#include <iostream>

int main() {
    Matrix4x4 A(
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        0, 0, 0, 1
    );

    Matrix4x4 B(
        2, 0, 1, 0,
        0, 1, 0, 0,
        1, 0, 2, 0,
        0, 0, 0, 1
    );

    Matrix4x4 G(
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        0, 0, 0, 1
    );

    Matrix4x4 H(
        2, 0, 1, 0,
        0, 1, 0, 0,
        1, 0, 2, 0,
        0, 0, 0, 1
    );

    Matrix4x4 I(
        2, 0, 1, 0,
        0, 1, 0, 0,
        1, 0, 2, 0,
        0, 0, 0, 1
    );

    Matrix4x4 C = A + B;
    std::cout << "A + B =\n";
    C.print();
    std::cout << "\n";

    Matrix4x4 D = A * 2.0f;
    std::cout << "A * 2 =\n";
    D.print();
    std::cout << "\n";

    Matrix4x4 E = A * B;
    Matrix4x4 F = B * A;
    std::cout << "A * B =\n";
    E.print();
    std::cout << "\n";

    std::cout << "B * A =\n";
    F.print();
    std::cout << "\n";

    if (E != F)
        std::cout << "Macierze A*B i B*A są różne — mnożenie nie jest przemienne.\n\n";

    G.LoadIdentity();
    std::cout << "Macierz jednostkowa I:\n";
    G.print();
    std::cout << "\n";

    H.setMatrixAsTransposeOfGivenMatrix(A);
    std::cout << "Transpozycja macierzy A:\n";
    H.print();
    std::cout << "\n";

    Vector4 v(1, 0, 0, 1);
    float angle = 90.0f;
    I.SetRotationY(angle);

    Vector4 v_rot = I * v;
    std::cout << "Wektor po obrocie 90 stopni wokół osi Y:\n";
    v_rot.print("rotated");
    std::cout << "\n";

    return 0;
}
