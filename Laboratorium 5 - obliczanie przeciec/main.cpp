#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

// --- STRUKTURY DANYCH ---

struct Point3D {
    double x, y, z;
};

struct Vector3D {
    double x, y, z;
};

struct Line3D {
    Point3D P;
    Vector3D v;
};

struct Plane {
    double A, B, C, D;
};

// --- FUNKCJE MATEMATYCZNE I POMOCNICZE ---

double dotProduct(Vector3D a, Vector3D b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3D crossProduct(Vector3D a, Vector3D b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

double vectorLength(Vector3D v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3D createVector(Point3D A, Point3D B) {
    return { B.x - A.x, B.y - A.y, B.z - A.z };
}

bool solveSystem2x2(double a1, double b1, double c1,
    double a2, double b2, double c2,
    double& outX, double& outY) {
    double W = a1 * b2 - a2 * b1;
    if (abs(W) < 1e-9) return false;

    double Wx = c1 * b2 - c2 * b1;
    double Wy = a1 * c2 - a2 * c1;

    outX = Wx / W;
    outY = Wy / W;
    return true;
}

bool findClosestPointsOnLines(Line3D L1, Line3D L2, double& t, double& s) {
    Vector3D w = { L1.P.x - L2.P.x, L1.P.y - L2.P.y, L1.P.z - L2.P.z };

    double a = dotProduct(L1.v, L1.v);
    double b = dotProduct(L1.v, L2.v);
    double c = dotProduct(L2.v, L2.v);
    double d = dotProduct(L1.v, w);
    double e = dotProduct(L2.v, w);

    double denominator = a * c - b * b;

    if (abs(denominator) < 1e-9) {
        return false;
    }

    t = (b * e - c * d) / denominator;
    s = (a * e - b * d) / denominator;

    return true;
}

Point3D getPointOnLine(Line3D L, double t) {
    return { L.P.x + t * L.v.x, L.P.y + t * L.v.y, L.P.z + t * L.v.z };
}

// --- ZADANIA ---

// Zadanie 1: Punkt przecięcia prostych
void zadanie1() {
    cout << "\n=== ZADANIE 1 ===\n";

    Line3D L1 = { {-2, 4, 0}, {3, 1, 5} };
    Line3D L2 = { {-2, 4, 0}, {1, -5, 3} };

    cout << "Prosta A: P=(" << L1.P.x << "," << L1.P.y << "," << L1.P.z << ") + t[" << L1.v.x << "," << L1.v.y << "," << L1.v.z << "]\n";
    cout << "Prosta B: P=(" << L2.P.x << "," << L2.P.y << "," << L2.P.z << ") + s[" << L2.v.x << "," << L2.v.y << "," << L2.v.z << "]\n";

    double t, s;
    if (findClosestPointsOnLines(L1, L2, t, s)) {
        Point3D P1 = getPointOnLine(L1, t);
        Point3D P2 = getPointOnLine(L2, s);

        double dist = sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2) + pow(P1.z - P2.z, 2));

        if (dist < 1e-5) {
            cout << "Punkt przeciecia: (" << P1.x << ", " << P1.y << ", " << P1.z << ")\n";
        }
        else {
            cout << "Proste sa skosne (mijaja sie). Min. dystans: " << dist << "\n";
        }
    }
    else {
        cout << "Proste sa rownolegle.\n";
    }
}

// Zadanie 2: Kąt między prostymi
void zadanie2() {
    cout << "\n=== ZADANIE 2 ===\n";
    Vector3D v1 = { 3, 1, 5 };
    Vector3D v2 = { 1, -5, 3 };

    double dot = dotProduct(v1, v2);
    double len1 = vectorLength(v1);
    double len2 = vectorLength(v2);

    double cosAngle = abs(dot) / (len1 * len2);
    double angle = acos(cosAngle) * 180.0 / M_PI;

    cout << "v1=[" << v1.x << "," << v1.y << "," << v1.z << "], v2=[" << v2.x << "," << v2.y << "," << v2.z << "]\n";
    cout << "Kat = " << angle << " stopni\n";
}

// Zadanie 3: Przecięcie prostej i płaszczyzny
void zadanie3() {
    cout << "\n=== ZADANIE 3 ===\n";
    Line3D L = { {-2, 2, -1}, {3, -1, 2} };
    Plane P = { 2, 3, 3, -8 };

    double denominator = P.A * L.v.x + P.B * L.v.y + P.C * L.v.z;

    if (abs(denominator) < 1e-9) {
        cout << "Prosta jest rownolegla do plaszczyzny.\n";
    }
    else {
        double numerator = P.A * L.P.x + P.B * L.P.y + P.C * L.P.z + P.D;
        double t = -numerator / denominator;
        Point3D intersection = getPointOnLine(L, t);

        cout << "t = " << t << "\n";
        cout << "Punkt przeciecia: (" << intersection.x << ", " << intersection.y << ", " << intersection.z << ")\n";
    }
}

// Zadanie 4: Kąt między prostą a płaszczyzną
void zadanie4() {
    cout << "\n=== ZADANIE 4 ===\n";
    Vector3D v = { 3, -1, 2 };
    Vector3D n = { 2, 3, 3 };

    double dot = abs(dotProduct(v, n));
    double lenV = vectorLength(v);
    double lenN = vectorLength(n);

    double sinAngle = dot / (lenV * lenN);
    double angle = asin(sinAngle) * 180.0 / M_PI;

    cout << "Kat = " << angle << " stopni\n";
}

// Zadanie 5: Prosta przecięcia płaszczyzn
void zadanie5() {
    cout << "\n=== ZADANIE 5 ===\n";
    Plane P1 = { 2, -1, 1, -8 };
    Plane P2 = { 4, 3, 1, 14 };

    Vector3D n1 = { P1.A, P1.B, P1.C };
    Vector3D n2 = { P2.A, P2.B, P2.C };
    Vector3D v = crossProduct(n1, n2);

    cout << "Wektor kierunkowy prostej v = [" << v.x << ", " << v.y << ", " << v.z << "]\n";

    Point3D P0;
    if (abs(v.z) >= abs(v.x) && abs(v.z) >= abs(v.y)) {
        double x, y;
        if (solveSystem2x2(P1.A, P1.B, -P1.D, P2.A, P2.B, -P2.D, x, y))
            P0 = { x, y, 0 };
    }
    else if (abs(v.y) >= abs(v.x)) {
        double x, z;
        if (solveSystem2x2(P1.A, P1.C, -P1.D, P2.A, P2.C, -P2.D, x, z))
            P0 = { x, 0, z };
    }
    else {
        double y, z;
        if (solveSystem2x2(P1.B, P1.C, -P1.D, P2.B, P2.C, -P2.D, y, z))
            P0 = { 0, y, z };
    }

    cout << "Rownanie parametryczne:\n";
    cout << "x = " << P0.x << " + (" << v.x << ")t\n";
    cout << "y = " << P0.y << " + (" << v.y << ")t\n";
    cout << "z = " << P0.z << " + (" << v.z << ")t\n";
}

// Zadanie 6: Kąt między płaszczyznami
void zadanie6() {
    cout << "\n=== ZADANIE 6 ===\n";
    Vector3D n1 = { 2, -1, 1 };
    Vector3D n2 = { 4, 3, 1 };

    double dot = dotProduct(n1, n2);
    double len1 = vectorLength(n1);
    double len2 = vectorLength(n2);

    double cosAngle = abs(dot) / (len1 * len2);
    double angle = acos(cosAngle) * 180.0 / M_PI;

    cout << "Kat = " << angle << " stopni\n";
}

// Zadanie 7: Przecięcie odcinków
void zadanie7() {
    cout << "\n=== ZADANIE 7 ===\n";
    Point3D A = { 5, 5, 4 }, A_end = { 10, 10, 6 };
    Point3D B = { 5, 5, 5 }, B_end = { 10, 10, 3 };

    Line3D Seg1 = { A, createVector(A, A_end) };
    Line3D Seg2 = { B, createVector(B, B_end) };

    double t, s;
    if (findClosestPointsOnLines(Seg1, Seg2, t, s)) {
        Point3D P1 = getPointOnLine(Seg1, t);
        Point3D P2 = getPointOnLine(Seg2, s);

        double distSq = pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2) + pow(P1.z - P2.z, 2);

        if (distSq < 1e-9) {
            if (t >= -1e-9 && t <= 1.0 + 1e-9 && s >= -1e-9 && s <= 1.0 + 1e-9) {
                cout << "Odcinki przecinaja sie w punkcie: (" << P1.x << ", " << P1.y << ", " << P1.z << ")\n";
            }
            else {
                cout << "Proste sie przecinaja, ale poza odcinkami.\n";
            }
        }
        else {
            cout << "Odcinki sie mijaja.\n";
        }
    }
    else {
        cout << "Odcinki sa rownolegle.\n";
    }
}

// Zadanie 8: Sfera i prosta (3D)
void zadanie8() {
    cout << "\n=== ZADANIE 8 (Sfera) ===\n";
    double rSq = 26.0;
    Point3D Center = { 0, 0, 0 };

    Point3D A = { 3, -1, -2 };
    Point3D A_prime = { 5, 3, -4 };

    Vector3D v = createVector(A, A_prime);

    cout << "Sfera r^2=" << rSq << ", Srodek=(0,0,0)\n";
    cout << "Prosta: P=(" << A.x << "," << A.y << "," << A.z << ") + t[" << v.x << "," << v.y << "," << v.z << "]\n";

    Vector3D L = createVector(Center, A);

    double a = dotProduct(v, v);
    double b = 2 * dotProduct(L, v);
    double c = dotProduct(L, L) - rSq;

    double delta = b * b - 4 * a * c;

    if (delta < 0) {
        cout << "Brak punktow wspolnych (delta < 0).\n";
    }
    else {
        double t1 = (-b - sqrt(delta)) / (2 * a);
        Point3D sol1 = getPointOnLine({ A, v }, t1);
        cout << "Punkt 1 (t=" << t1 << "): (" << sol1.x << ", " << sol1.y << ", " << sol1.z << ")\n";

        if (delta > 1e-9) {
            double t2 = (-b + sqrt(delta)) / (2 * a);
            Point3D sol2 = getPointOnLine({ A, v }, t2);
            cout << "Punkt 2 (t=" << t2 << "): (" << sol2.x << ", " << sol2.y << ", " << sol2.z << ")\n";
        }
    }
}

// --- FUNKCJA GŁÓWNA ---

int main() {
    int choice;
    do {
        cout << "\nWYBIERZ ZADANIE: \n";
        cout << "1 - Zadanie 1 (Przeciecie prostych)\n";
        cout << "2 - Zadanie 2 (Kat miedzy prostymi)\n";
        cout << "3 - Zadanie 3 (Prosta i plaszczyzna)\n";
        cout << "4 - Zadanie 4 (Kat prosta-plaszczyzna)\n";
        cout << "5 - Zadanie 5 (Przeciecie plaszczyzn)\n";
        cout << "6 - Zadanie 6 (Kat miedzy plaszczyznami)\n";
        cout << "7 - Zadanie 7 (Odcinki)\n";
        cout << "8 - Zadanie dodatkowe (Sfera 3D)\n";
        cout << "10 - Wszystkie\n";
        cout << "0 - Wyjscie\n";
        cout << "Wybor: ";
        cin >> choice;

        switch (choice) {
        case 1: zadanie1(); break;
        case 2: zadanie2(); break;
        case 3: zadanie3(); break;
        case 4: zadanie4(); break;
        case 5: zadanie5(); break;
        case 6: zadanie6(); break;
        case 7: zadanie7(); break;
        case 8: zadanie8(); break;
        case 10:
            zadanie1(); zadanie2(); zadanie3(); zadanie4();
            zadanie5(); zadanie6(); zadanie7(); zadanie8();
            break;
        case 0: break;
        }
    } while (choice != 0);

    return 0;
}