// Definicja potrzebna, aby M_PI (liczba Pi) była dostępna w Visual Studio
#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

// ==========================================
// CZĘŚĆ 1: STRUKTURY DANYCH
// ==========================================

struct Point3D {
    double x, y, z;
};

struct Vector3D {
    double x, y, z;
};

// Struktura Prostej w postaci parametrycznej
// Każdy punkt na prostej to: P(t) = P_start + t * wektor_kierunku
struct Line3D {
    Point3D P;    // Punkt zaczepienia (startowy)
    Vector3D v;   // Wektor kierunkowy (dokąd prosta leci)
};

// Struktura Płaszczyzny: Ax + By + Cz + D = 0
// Wektor [A, B, C] to tzw. wektor normalny (prostopadły do płaszczyzny)
struct Plane {
    double A, B, C, D;
};

// ==========================================
// CZĘŚĆ 2: MATEMATYKA (HELPERS)
// ==========================================

// Iloczyn Skalarny (Dot Product)
// Wynik to liczba. Kluczowe zastosowania:
// 1. Liczenie kątów: a*b = |a||b| * cos(konta)
// 2. Sprawdzanie prostopadłości: jeśli a*b == 0, to wektory są prostopadłe.
double dotProduct(Vector3D a, Vector3D b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Iloczyn Wektorowy (Cross Product)
// Wynik to nowy wektor, który jest PROSTOPADŁY do obu wektorów wejściowych.
// Kluczowe do znalezienia normalnej płaszczyzny lub wspólnego kierunku prostopadłego.
Vector3D crossProduct(Vector3D a, Vector3D b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

// Długość wektora (Pitagoras w 3D)
double vectorLength(Vector3D v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Tworzy wektor od punktu A do punktu B (B - A)
Vector3D createVector(Point3D A, Point3D B) {
    return { B.x - A.x, B.y - A.y, B.z - A.z };
}

// Rozwiązywanie układu równań 2x2 metodą wyznaczników (Cramera)
// ax + by = c (dla dwóch równań)
// Przydaje się przy szukaniu przecięcia płaszczyzn.
bool solveSystem2x2(double a1, double b1, double c1,
    double a2, double b2, double c2,
    double& outX, double& outY) {

    double W = a1 * b2 - a2 * b1; // Wyznacznik główny

    // Jeśli wyznacznik bliski 0, układ jest sprzeczny lub nieoznaczony
    if (abs(W) < 1e-9) return false;

    double Wx = c1 * b2 - c2 * b1;
    double Wy = a1 * c2 - a2 * c1;

    outX = Wx / W;
    outY = Wy / W;
    return true;
}

// ==========================================
// NAJWAŻNIEJSZA FUNKCJA: ODLEGŁOŚĆ MIĘDZY PROSTYMI
// ==========================================
// Szuka parametrów t (dla L1) i s (dla L2) dla punktów, które są
// najbliżej siebie na obu prostych.
// Jeśli proste się przecinają, odległość między tymi punktami wyniesie 0.
bool findClosestPointsOnLines(Line3D L1, Line3D L2, double& t, double& s) {
    Vector3D w = { L1.P.x - L2.P.x, L1.P.y - L2.P.y, L1.P.z - L2.P.z };

    // Obliczamy iloczyny skalarne potrzebne do układu równań
    double a = dotProduct(L1.v, L1.v);
    double b = dotProduct(L1.v, L2.v);
    double c = dotProduct(L2.v, L2.v);
    double d = dotProduct(L1.v, w);
    double e = dotProduct(L2.v, w);

    double denominator = a * c - b * b;

    // Jeśli mianownik bliski 0, proste są równoległe -> nie przetną się
    if (abs(denominator) < 1e-9) return false;

    // Wyliczenie parametrów t i s (wzory wyprowadzone z pochodnych odległości)
    t = (b * e - c * d) / denominator;
    s = (a * e - b * d) / denominator;

    return true;
}

// Zwraca konkretny punkt w 3D dla danego parametru t
Point3D getPointOnLine(Line3D L, double t) {
    return { L.P.x + t * L.v.x, L.P.y + t * L.v.y, L.P.z + t * L.v.z };
}

// ==========================================
// CZĘŚĆ 3: ROZWIĄZANIA ZADAŃ
// ==========================================

// ZADANIE 1: Czy dwie proste się przecinają?
void zadanie1() {
    cout << "\n=== ZADANIE 1 (Przeciecie prostych) ===\n";

    // Dane wejściowe: Punkt + Wektor
    Line3D L1 = { {-2, 4, 0}, {3, 1, 5} };
    Line3D L2 = { {-2, 4, 0}, {1, -5, 3} };

    cout << "Sprawdzamy odleglosc miedzy prostymi...\n";

    double t, s;
    if (findClosestPointsOnLines(L1, L2, t, s)) {
        // Znajdujemy punkty najbliższe sobie na obu prostych
        Point3D P1 = getPointOnLine(L1, t);
        Point3D P2 = getPointOnLine(L2, s);

        // Liczymy dystans euklidesowy
        double dist = sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2) + pow(P1.z - P2.z, 2));

        // Używamy "epsilona" (1e-5), bo w floatach 0 rzadko jest idealnym zerem
        if (dist < 1e-5) {
            cout << "SUKCES! Przecinaja sie w: (" << P1.x << ", " << P1.y << ", " << P1.z << ")\n";
        }
        else {
            cout << "Mijaja sie (sa skosne). Minimalny dystans: " << dist << "\n";
        }
    }
    else {
        cout << "Sa rownolegle (brak punktu wspolnego).\n";
    }
}

// ZADANIE 2: Kąt między prostymi
void zadanie2() {
    cout << "\n=== ZADANIE 2 (Kat prostych) ===\n";
    Vector3D v1 = { 3, 1, 5 };
    Vector3D v2 = { 1, -5, 3 };

    // Wzór: cos(alpha) = |v1 * v2| / (|v1| * |v2|)
    // Używamy abs() w liczniku, bo interesuje nas kąt ostry (między 0 a 90 stopni)
    double dot = dotProduct(v1, v2);
    double len1 = vectorLength(v1);
    double len2 = vectorLength(v2);

    double cosAngle = abs(dot) / (len1 * len2);

    // acos zwraca radiany, zamieniamy na stopnie (* 180 / PI)
    double angle = acos(cosAngle) * 180.0 / M_PI;

    cout << "Kat = " << angle << " stopni\n";
}

// ZADANIE 3: Przecięcie prostej i płaszczyzny
void zadanie3() {
    cout << "\n=== ZADANIE 3 (Prosta i plaszczyzna) ===\n";
    Line3D L = { {-2, 2, -1}, {3, -1, 2} };
    Plane P = { 2, 3, 3, -8 }; // 2x + 3y + 3z - 8 = 0

    // Podstawiamy równania prostej (x = Px + tvx...) do równania płaszczyzny.
    // Otrzymujemy równanie z jedną niewiadomą 't'.
    // Mianownik to iloczyn skalarny wektora prostej i normalnej płaszczyzny.
    double denominator = P.A * L.v.x + P.B * L.v.y + P.C * L.v.z;

    if (abs(denominator) < 1e-9) {
        cout << "Prosta jest rownolegla do plaszczyzny (brak przeciecia).\n";
    }
    else {
        // Obliczamy t ze wzoru
        double numerator = P.A * L.P.x + P.B * L.P.y + P.C * L.P.z + P.D;
        double t = -numerator / denominator;

        Point3D intersection = getPointOnLine(L, t);
        cout << "t = " << t << "\n";
        cout << "Punkt przeciecia: (" << intersection.x << ", " << intersection.y << ", " << intersection.z << ")\n";
    }
}

// ZADANIE 4: Kąt między prostą a płaszczyzną
void zadanie4() {
    cout << "\n=== ZADANIE 4 (Kat prosta-plaszczyzna) ===\n";
    Vector3D v = { 3, -1, 2 }; // Wektor prostej
    Vector3D n = { 2, 3, 3 };  // Wektor normalny płaszczyzny

    // UWAGA: Licząc kąt między wektorem prostej a wektorem normalnym płaszczyzny,
    // dostajemy kąt "do pionu". Kąt z samą płaszczyzną to dopełnienie do 90 stopni.
    // Dlatego używamy asin() zamiast acos() albo 90 - wynik.
    // Wzór: sin(alpha) = |v * n| / (|v| * |n|)

    double dot = abs(dotProduct(v, n));
    double lenV = vectorLength(v);
    double lenN = vectorLength(n);

    double sinAngle = dot / (lenV * lenN);
    double angle = asin(sinAngle) * 180.0 / M_PI;

    cout << "Kat = " << angle << " stopni\n";
}

// ZADANIE 5: Przecięcie dwóch płaszczyzn
// Wynikiem przecięcia dwóch płaszczyzn jest PROSTA.
void zadanie5() {
    cout << "\n=== ZADANIE 5 (Przeciecie plaszczyzn) ===\n";
    Plane P1 = { 2, -1, 1, -8 };
    Plane P2 = { 4, 3, 1, 14 };

    Vector3D n1 = { P1.A, P1.B, P1.C };
    Vector3D n2 = { P2.A, P2.B, P2.C };

    // 1. Kierunek prostej wynikowej jest prostopadły do obu normalnych.
    // Liczymy iloczyn wektorowy.
    Vector3D v = crossProduct(n1, n2);
    cout << "Kierunek prostej v = [" << v.x << ", " << v.y << ", " << v.z << "]\n";

    // 2. Musimy znaleźć jakikolwiek punkt zaczepienia (P0) na tej prostej.
    // Prosta przecina przynajmniej jedną z płaszczyzn układu (XY, XZ lub YZ).
    // Zakładamy jedną zmienną = 0 i rozwiązujemy układ równań dla pozostałych dwóch.

    Point3D P0;
    // Sprawdzamy, która składowa wektora jest największa (unikanie dzielenia przez 0)
    if (abs(v.z) >= abs(v.x) && abs(v.z) >= abs(v.y)) {
        // Zakładamy z=0, szukamy x i y
        double x, y;
        if (solveSystem2x2(P1.A, P1.B, -P1.D, P2.A, P2.B, -P2.D, x, y))
            P0 = { x, y, 0 };
    }
    else if (abs(v.y) >= abs(v.x)) {
        // Zakładamy y=0, szukamy x i z
        double x, z;
        if (solveSystem2x2(P1.A, P1.C, -P1.D, P2.A, P2.C, -P2.D, x, z))
            P0 = { x, 0, z };
    }
    else {
        // Zakładamy x=0, szukamy y i z
        double y, z;
        if (solveSystem2x2(P1.B, P1.C, -P1.D, P2.B, P2.C, -P2.D, y, z))
            P0 = { 0, y, z };
    }

    cout << "Prosta parametryczna:\n";
    cout << "x = " << P0.x << " + (" << v.x << ")t\n";
    cout << "y = " << P0.y << " + (" << v.y << ")t\n";
    cout << "z = " << P0.z << " + (" << v.z << ")t\n";
}

// ZADANIE 6: Kąt między dwiema płaszczyznami
void zadanie6() {
    cout << "\n=== ZADANIE 6 (Kat plaszczyzn) ===\n";
    // Kąt między płaszczyznami to kąt między ich wektorami normalnymi.
    Vector3D n1 = { 2, -1, 1 };
    Vector3D n2 = { 4, 3, 1 };

    double dot = dotProduct(n1, n2);
    double len1 = vectorLength(n1);
    double len2 = vectorLength(n2);

    double cosAngle = abs(dot) / (len1 * len2);
    double angle = acos(cosAngle) * 180.0 / M_PI;

    cout << "Kat = " << angle << " stopni\n";
}

// ZADANIE 7: Przecięcie odcinków (Segmentów)
// To samo co proste, ale musimy sprawdzić czy punkt leży "pomiędzy" końcami.
void zadanie7() {
    cout << "\n=== ZADANIE 7 (Odcinki) ===\n";
    Point3D A = { 5, 5, 4 }, A_end = { 10, 10, 6 };
    Point3D B = { 5, 5, 5 }, B_end = { 10, 10, 3 };

    // Tworzymy proste nieskończone na bazie odcinków
    Line3D Seg1 = { A, createVector(A, A_end) };
    Line3D Seg2 = { B, createVector(B, B_end) };

    double t, s;
    if (findClosestPointsOnLines(Seg1, Seg2, t, s)) {
        Point3D P1 = getPointOnLine(Seg1, t);
        Point3D P2 = getPointOnLine(Seg2, s);

        double distSq = pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2) + pow(P1.z - P2.z, 2);

        // Jeśli proste nieskończone się przecinają (dystans ~0)
        if (distSq < 1e-9) {
            // KLUCZOWE DLA ODCINKÓW: Parametry t i s muszą być w przedziale [0, 1]
            // t=0 to początek odcinka, t=1 to koniec.
            if (t >= -1e-9 && t <= 1.0 + 1e-9 && s >= -1e-9 && s <= 1.0 + 1e-9) {
                cout << "Przecinaja sie wewnatrz odcinkow: (" << P1.x << ", " << P1.y << ", " << P1.z << ")\n";
            }
            else {
                cout << "Proste sie przecinaja, ale POZA odcinkami (t=" << t << ", s=" << s << ")\n";
            }
        }
        else {
            cout << "Odcinki mijaja sie (brak przeciecia).\n";
        }
    }
    else {
        cout << "Odcinki rownolegle.\n";
    }
}

// ZADANIE 8: Przecięcie prostej i sfery
void zadanie8() {
    cout << "\n=== ZADANIE 8 (Sfera i prosta) ===\n";
    // Równanie sfery: (x-cx)^2 + (y-cy)^2 + (z-cz)^2 = r^2
    double rSq = 26.0;         // r^2
    Point3D Center = { 0, 0, 0 }; // Środek sfery

    // Prosta przechodząca przez A i A_prime
    Point3D A = { 3, -1, -2 };
    Point3D A_prime = { 5, 3, -4 };
    Vector3D v = createVector(A, A_prime);

    // Aby znaleźć przecięcie, wstawiamy równanie prostej do równania sfery.
    // Otrzymujemy równanie kwadratowe: at^2 + bt + c = 0
    // L to wektor od środka sfery do początku prostej
    Vector3D L = createVector(Center, A);

    double a = dotProduct(v, v);
    double b = 2 * dotProduct(L, v);
    double c = dotProduct(L, L) - rSq;

    // Liczymy deltę
    double delta = b * b - 4 * a * c;

    if (delta < 0) {
        cout << "Delta < 0: Prosta omija sfere.\n";
    }
    else {
        // t1 i t2 to rozwiązania równania kwadratowego (momenty trafienia)
        double t1 = (-b - sqrt(delta)) / (2 * a);
        Point3D sol1 = getPointOnLine({ A, v }, t1);
        cout << "Punkt trafienia 1: (" << sol1.x << ", " << sol1.y << ", " << sol1.z << ")\n";

        if (delta > 1e-9) { // Jeśli delta > 0, są dwa rozwiązania
            double t2 = (-b + sqrt(delta)) / (2 * a);
            Point3D sol2 = getPointOnLine({ A, v }, t2);
            cout << "Punkt trafienia 2: (" << sol2.x << ", " << sol2.y << ", " << sol2.z << ")\n";
        }
        else {
            cout << "Delta = 0: Prosta jest styczna do sfery (1 punkt).\n";
        }
    }
}

// ==========================================
// MAIN - MENU GLOWNE
// ==========================================
int main() {
    int choice;
    do {
        cout << "\n--- GEOMETRIA ANALITYCZNA 3D ---\n";
        cout << "1 - Przeciecie prostych\n";
        cout << "2 - Kat miedzy prostymi\n";
        cout << "3 - Przeciecie prostej i plaszczyzny\n";
        cout << "4 - Kat prosta-plaszczyzna\n";
        cout << "5 - Przeciecie dwoch plaszczyzn\n";
        cout << "6 - Kat miedzy plaszczyznami\n";
        cout << "7 - Przeciecie odcinkow\n";
        cout << "8 - Przeciecie prostej i sfery\n";
        cout << "10 - Uruchom wszystko\n";
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
        default: cout << "Nieznana opcja.\n";
        }
    } while (choice != 0);

    return 0;
}