#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

// --- STRUKTURY ---

struct Point3D {
    double x, y, z;
};

struct Vector3D {
    double x, y, z;
};

struct Line3D {
    Point3D P;    // punkt startowy
    Vector3D v;   // wektor kierunkowy
    // wzor: P(t) = P + t*v
};

struct Plane {
    double A, B, C, D; 
    // rownanie ogolne: Ax + By + Cz + D = 0
    // normalna n = [A, B, C]
};

// --- POMOCNICZE ---

// iloczyn skalarny: a*b = ax*bx + ay*by + az*bz
double dotProduct(Vector3D a, Vector3D b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// iloczyn wektorowy (cross product)
// daje wektor prostopadly do dwoch pozostalych
Vector3D crossProduct(Vector3D a, Vector3D b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

// dlugosc wektora
double vectorLength(Vector3D v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// robi wektor z dwoch punktow: B - A
Vector3D createVector(Point3D A, Point3D B) {
    return {B.x - A.x, B.y - A.y, B.z - A.z};
}

// cramer do ukladu 2x2, przydaje sie pozniej
bool solveSystem2x2(double a1, double b1, double c1,
                    double a2, double b2, double c2,
                    double &outX, double &outY) {
    double W = a1 * b2 - a2 * b1;
    if (abs(W) < 1e-9) return false;

    double Wx = c1 * b2 - c2 * b1;
    double Wy = a1 * c2 - a2 * c1;

    outX = Wx / W;
    outY = Wy / W;
    return true;
}

// algorytm szukajacy najblizszych punktow na prostych
// wylicza parametry t i s
// jak proste sie przecinaja to odleglosc wyjdzie 0
bool findClosestPointsOnLines(Line3D L1, Line3D L2, double &t, double &s) {
    Vector3D w = {L1.P.x - L2.P.x, L1.P.y - L2.P.y, L1.P.z - L2.P.z};

    double a = dotProduct(L1.v, L1.v); 
    double b = dotProduct(L1.v, L2.v); 
    double c = dotProduct(L2.v, L2.v); 
    double d = dotProduct(L1.v, w);    
    double e = dotProduct(L2.v, w);    

    double denominator = a * c - b * b;

    if (abs(denominator) < 1e-9) return false; // rownolegle

    t = (b * e - c * d) / denominator;
    s = (a * e - b * d) / denominator;

    return true;
}

Point3D getPointOnLine(Line3D L, double t) {
    return {L.P.x + t * L.v.x, L.P.y + t * L.v.y, L.P.z + t * L.v.z};
}

// --- ZADANKA ---

// zad 1 - punkt przeciecia prostych
void zadanie1() {
    cout << "\n=== ZADANIE 1 ===\n";
    
    // prosta A z zadania
    // (x+2)/3 = y-4 = z/5
    // punkt (-2, 4, 0), wektor [3, 1, 5]
    Line3D L1 = { {-2, 4, 0}, {3, 1, 5} };

    // prosta B
    // (x+2)/1 = -1/5(y-4) = z/3
    // uwaga: srodkowy czlon to (y-4)/-5 wiec wspolrzedna y wektora to -5!
    Line3D L2 = { {-2, 4, 0}, {1, -5, 3} };

    cout << "Prosta A: P=(" << L1.P.x << "," << L1.P.y << "," << L1.P.z << ") + t[" << L1.v.x << "," << L1.v.y << "," << L1.v.z << "]\n";
    cout << "Prosta B: P=(" << L2.P.x << "," << L2.P.y << "," << L2.P.z << ") + s[" << L2.v.x << "," << L2.v.y << "," << L2.v.z << "]\n";

    double t, s;
    // sprawdzamy czy sie stykaja
    if (findClosestPointsOnLines(L1, L2, t, s)) {
        Point3D P1 = getPointOnLine(L1, t);
        Point3D P2 = getPointOnLine(L2, s);
        
        // liczymy dystans miedzy punktami na obu prostych
        double dist = sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2) + pow(P1.z - P2.z, 2));
        
        if (dist < 1e-5) {
             cout << "Punkt przeciecia: (" << P1.x << ", " << P1.y << ", " << P1.z << ")\n";
        } else {
             cout << "Mijaja sie (skosne). Dystans: " << dist << "\n";
        }
    } else {
        cout << "Rownolegle sa.\n";
    }
}

// zad 2 - kat miedzy prostymi
void zadanie2() {
    cout << "\n=== ZADANIE 2 ===\n";
    // wektory z zad 1
    Vector3D v1 = {3, 1, 5};
    Vector3D v2 = {1, -5, 3};

    // wzor na cosinus kata miedzy wektorami
    // cos = |v1*v2| / (|v1|*|v2|)
    double dot = dotProduct(v1, v2);
    double len1 = vectorLength(v1);
    double len2 = vectorLength(v2);

    double cosAngle = abs(dot) / (len1 * len2); // abs bo kat ostry
    double angle = acos(cosAngle) * 180.0 / M_PI;

    cout << "v1=[" << v1.x << "," << v1.y << "," << v1.z << "], v2=[" << v2.x << "," << v2.y << "," << v2.z << "]\n";
    cout << "Kat = " << angle << " stopni\n";
}

// zad 3 - prosta i plaszczyzna
void zadanie3() {
    cout << "\n=== ZADANIE 3 ===\n";
    // prosta z parametrycznego: P(-2, 2, -1), v(3, -1, 2)
    Line3D L = { {-2, 2, -1}, {3, -1, 2} };
    
    // plaszczyzna 2x + 3y + 3z - 8 = 0
    // normalna [2, 3, 3], D = -8
    Plane P = { 2, 3, 3, -8 };

    // podstawiamy rownanie prostej do plaszczyzny
    // wyliczamy t z wzoru: t = -(Ax0 + By0 + Cz0 + D) / (Avx + Bvy + Cvz)
    
    double denominator = P.A * L.v.x + P.B * L.v.y + P.C * L.v.z;
    
    if (abs(denominator) < 1e-9) {
        cout << "Rownolegla (nie przecina).\n";
    } else {
        double numerator = P.A * L.P.x + P.B * L.P.y + P.C * L.P.z + P.D;
        double t = -numerator / denominator;
        Point3D intersection = getPointOnLine(L, t);

        cout << "t = " << t << "\n";
        cout << "Punkt: (" << intersection.x << ", " << intersection.y << ", " << intersection.z << ")\n";
    }
}

// zad 4 - kat prosta/plaszczyzna
void zadanie4() {
    cout << "\n=== ZADANIE 4 ===\n";
    // wektory z zad 3
    Vector3D v = {3, -1, 2};
    Vector3D n = {2, 3, 3};

    // uwaga: tu liczymy kat z normalna, wiec wychodzi 90-alfa
    // dlatego uzywamy sinusa zamiast cosinusa
    // sin(alfa) = |v*n| / (|v|*|n|)
    
    double dot = abs(dotProduct(v, n));
    double lenV = vectorLength(v);
    double lenN = vectorLength(n);

    double sinAngle = dot / (lenV * lenN);
    double angle = asin(sinAngle) * 180.0 / M_PI;

    cout << "Kat = " << angle << " stopni\n";
}

// zad 5 - przeciecie dwoch plaszczyzn
void zadanie5() {
    cout << "\n=== ZADANIE 5 ===\n";
    // plaszczyzna A: 2x - y + z - 8 = 0
    Plane P1 = {2, -1, 1, -8};
    // plaszczyzna B: 4x + 3y + z + 14 = 0
    Plane P2 = {4, 3, 1, 14};

    Vector3D n1 = {P1.A, P1.B, P1.C};
    Vector3D n2 = {P2.A, P2.B, P2.C};
    
    // kierunek prostej to iloczyn wektorowy obu normalnych
    Vector3D v = crossProduct(n1, n2);

    cout << "Wektor kierunkowy v = [" << v.x << ", " << v.y << ", " << v.z << "]\n";

    // trzeba znalezc jakis punkt wspolny (P0)
    // zakladamy z=0 i liczymy uklad rownan dla x,y
    Point3D P0;
    // sprawdzam ktora wspolrzedna v jest najwieksza zeby nie dzielic przez zero
    if (abs(v.z) >= abs(v.x) && abs(v.z) >= abs(v.y)) {
        // z=0
        double x, y;
        if(solveSystem2x2(P1.A, P1.B, -P1.D, P2.A, P2.B, -P2.D, x, y)) 
            P0 = {x, y, 0};
    } else if (abs(v.y) >= abs(v.x)) {
        // y=0
        double x, z;
        if(solveSystem2x2(P1.A, P1.C, -P1.D, P2.A, P2.C, -P2.D, x, z))
            P0 = {x, 0, z};
    } else {
        // x=0
        double y, z;
        if(solveSystem2x2(P1.B, P1.C, -P1.D, P2.B, P2.C, -P2.D, y, z))
            P0 = {0, y, z};
    }

    cout << "Rownanie:\n";
    cout << "x = " << P0.x << " + (" << v.x << ")t\n";
    cout << "y = " << P0.y << " + (" << v.y << ")t\n";
    cout << "z = " << P0.z << " + (" << v.z << ")t\n";
}

// zad 6 - kat miedzy plaszczyznami
void zadanie6() {
    cout << "\n=== ZADANIE 6 ===\n";
    // kat miedzy normalnymi
    Vector3D n1 = {2, -1, 1};
    Vector3D n2 = {4, 3, 1};

    // standardowy wzor z cosinusem
    double dot = dotProduct(n1, n2);
    double len1 = vectorLength(n1);
    double len2 = vectorLength(n2);

    double cosAngle = abs(dot) / (len1 * len2);
    double angle = acos(cosAngle) * 180.0 / M_PI;

    cout << "Kat = " << angle << " stopni\n";
}

// zad 7 - odcinki
void zadanie7() {
    cout << "\n=== ZADANIE 7 ===\n";
    // punkty z tresci
    Point3D A = {5, 5, 4}, A_end = {10, 10, 6};
    Point3D B = {5, 5, 5}, B_end = {10, 10, 3};

    // robimy proste z odcinkow
    Line3D Seg1 = { A, createVector(A, A_end) };
    Line3D Seg2 = { B, createVector(B, B_end) };

    double t, s;
    if (findClosestPointsOnLines(Seg1, Seg2, t, s)) {
        Point3D P1 = getPointOnLine(Seg1, t);
        Point3D P2 = getPointOnLine(Seg2, s);

        double distSq = pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2) + pow(P1.z - P2.z, 2);

        // jak sa blisko siebie to sprawdzamy czy naleza do odcinkow
        if (distSq < 1e-9) { 
            // t i s musza byc miedzy 0 a 1
            if (t >= -1e-9 && t <= 1.0 + 1e-9 && s >= -1e-9 && s <= 1.0 + 1e-9) {
                cout << "Przecinaja sie w: (" << P1.x << ", " << P1.y << ", " << P1.z << ")\n";
            } else {
                cout << "Przecinaja sie proste, ale poza odcinkami (t=" << t << ", s=" << s << ")\n";
            }
        } else {
            cout << "Mijaja sie.\n";
        }
    } else {
        cout << "Rownolegle.\n";
    }
}

// zad 8 - sfera 3d
void zadanie8() {
    cout << "\n=== ZADANIE 8 (Sfera) ===\n";
    // Sfera w (0,0,0), promien sqrt(26) -> r^2 = 26
    double rSq = 26.0;
    Point3D Center = {0, 0, 0};

    // Prosta przez punkty A i A'
    Point3D A = {3, -1, -2};
    Point3D A_prime = {5, 3, -4};
    
    Vector3D v = createVector(A, A_prime);

    cout << "Sfera r^2=" << rSq << "\n";
    cout << "Prosta: P=(" << A.x << "," << A.y << "," << A.z << ") + t[" << v.x << "," << v.y << "," << v.z << "]\n";

    // wstawiamy prosta do rownania sfery i wychodzi f. kwadratowa
    // at^2 + bt + c = 0
    Vector3D L = createVector(Center, A);

    double a = dotProduct(v, v);
    double b = 2 * dotProduct(L, v);
    double c = dotProduct(L, L) - rSq;

    // delta
    double delta = b*b - 4*a*c;

    if (delta < 0) {
        cout << "Brak wspolnych (delta ujemna).\n";
    } else {
        double t1 = (-b - sqrt(delta)) / (2*a);
        Point3D sol1 = getPointOnLine({A, v}, t1);
        cout << "Punkt 1: (" << sol1.x << ", " << sol1.y << ", " << sol1.z << ")\n";

        if (delta > 1e-9) {
            double t2 = (-b + sqrt(delta)) / (2*a);
            Point3D sol2 = getPointOnLine({A, v}, t2);
            cout << "Punkt 2: (" << sol2.x << ", " << sol2.y << ", " << sol2.z << ")\n";
        }
    }
}

// --- MAIN ---

int main() {
    int choice;
    do {
        cout << "\nWYBIERZ ZADANIE: \n";
        cout << "1-7 zadania z listy, 8 to sfera\n";
        cout << "10 - Wszystkie na raz\n";
        cout << "0 - Wyjscie\n";
        cout << "Wybor: ";
        cin >> choice;

        switch(choice) {
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