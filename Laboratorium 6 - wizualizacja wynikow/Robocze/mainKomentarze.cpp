#include <iostream> // Do wypisywania na ekran (cout, cin)
#include <vector>   // Kontenery danych (nieużywane tutaj intensywnie, ale warto mieć)
#include <cmath>    // Matematyka: sqrt (pierwiastek), sin, cos, abs (wartość bezwzględna)
#include <algorithm>// Funkcje pomocnicze: swap, max, min
#include <string>   // Obsługa napisów (do buforowania obrazu)

// ==========================================
// 1. STRUKTURA WEKTORA (VEC3)
// W grafice 3D wszystko jest wektorem: pozycja punktu, kierunek patrzenia, kolor.
// ==========================================
struct Vec3 {
    double x, y, z;

    // Dodawanie wektorów (przesuwanie punktu)
    Vec3 operator+(const Vec3& v) const { return {x + v.x, y + v.y, z + v.z}; }

    // Odejmowanie wektorów (wektor od punktu A do B to B - A)
    Vec3 operator-(const Vec3& v) const { return {x - v.x, y - v.y, z - v.z}; }

    // Mnożenie przez liczbę (skalowanie, np. wydłużenie wektora)
    Vec3 operator*(double t) const { return {x * t, y * t, z * t}; }

    // Iloczyn skalarny (Dot Product)
    // Jeśli wynik = 0, wektory są prostopadłe. Używane w oświetleniu i kątach.
    double dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }

    // Iloczyn wektorowy (Cross Product)
    // Zwraca wektor prostopadły do dwóch podanych.
    // KLUCZOWE DLA KAMERY: Jeśli mamy wektor "Do Przodu" i "W Górę",
    // to iloczyn wektorowy da nam wektor "W Prawo".
    Vec3 cross(const Vec3& v) const {
        return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
    }

    // Normalizacja (Unit Vector)
    // Zmienia długość wektora na 1, zachowując kierunek.
    // W ray tracingu kierunki ZAWSZE muszą mieć długość 1.
    Vec3 unit() const {
        double len = std::sqrt(x*x + y*y + z*z);
        return (len > 0) ? Vec3{x/len, y/len, z/len} : Vec3{0,0,0};
    }
};

// ==========================================
// 2. STRUKTURA PROMIENIA (RAY)
// Promień to linia w przestrzeni.
// ==========================================
struct Ray {
    Vec3 origin;    // Skąd wychodzi (kamera)
    Vec3 direction; // Gdzie leci (musi być znormalizowany)
};

// ==========================================
// 3. BRYŁA: SZEŚCIAN (AABB)
// Axis-Aligned Bounding Box - Pudełko wyrównane do osi.
// Definiujemy je przez dwa przeciwległe rogi: min i max.
// ==========================================
struct Cube {
    Vec3 minBound; // Lewy-dolny-tylny róg (np. -1, -1, -1)
    Vec3 maxBound; // Prawy-górny-przedni róg (np. 1, 1, 1)

    // Funkcja sprawdzająca, czy promień trafił w pudełko.
    // Algorytm "Slab Method" (Metoda Płyt):
    // Sprawdzamy, kiedy promień wchodzi i wychodzi z obszaru X, Y i Z.
    // Jeśli te przedziały czasowe się nakładają -> mamy trafienie.
    bool hit(const Ray& r) const {
        double t_min = 0.0;       // Najwcześniejszy moment wejścia
        double t_max = 100000.0;  // Najpóźniejszy moment wyjścia

        // --- Sprawdzanie osi X ---
        if (std::abs(r.direction.x) < 1e-5) {
            // Jeśli promień jest równoległy do osi X i jest poza pudełkiem -> pudło
             if (r.origin.x < minBound.x || r.origin.x > maxBound.x) return false;
        } else {
            // Obliczamy moment wejścia (t0) i wyjścia (t1) dla płaszczyzn X
            double invD = 1.0 / r.direction.x;
            double t0 = (minBound.x - r.origin.x) * invD;
            double t1 = (maxBound.x - r.origin.x) * invD;

            if (t0 > t1) std::swap(t0, t1); // Upewniamy się, że t0 to wejście, t1 to wyjście

            // Zawężamy przedział trafienia
            t_min = std::max(t_min, t0);
            t_max = std::min(t_max, t1);

            // Jeśli moment wejścia jest później niż wyjścia -> promień minął pudełko
            if (t_min > t_max) return false;
        }

        // --- Sprawdzanie osi Y (To samo co dla X) ---
        if (std::abs(r.direction.y) < 1e-5) {
             if (r.origin.y < minBound.y || r.origin.y > maxBound.y) return false;
        } else {
            double invD = 1.0 / r.direction.y;
            double t0 = (minBound.y - r.origin.y) * invD;
            double t1 = (maxBound.y - r.origin.y) * invD;
            if (t0 > t1) std::swap(t0, t1);
            t_min = std::max(t_min, t0); t_max = std::min(t_max, t1);
            if (t_min > t_max) return false;
        }

        // --- Sprawdzanie osi Z (To samo co dla X) ---
        if (std::abs(r.direction.z) < 1e-5) {
             if (r.origin.z < minBound.z || r.origin.z > maxBound.z) return false;
        } else {
            double invD = 1.0 / r.direction.z;
            double t0 = (minBound.z - r.origin.z) * invD;
            double t1 = (maxBound.z - r.origin.z) * invD;
            if (t0 > t1) std::swap(t0, t1);
            t_min = std::max(t_min, t0); t_max = std::min(t_max, t1);
            if (t_min > t_max) return false;
        }

        return true; // Przeszliśmy wszystkie testy -> trafienie!
    }
};

// Funkcja "czyszcząca" ekran przez wypisanie pustych linii.
// Działa na każdym systemie (Windows/Linux/Mac), w przeciwieństwie do system("cls").
void clearScreen() {
    for(int i=0; i<50; i++) std::cout << "\n";
}

// ==========================================
// 4. GŁÓWNA PĘTLA PROGRAMU
// ==========================================
int main() {
    // Tworzymy sześcian od (-1,-1,-1) do (1,1,1) w centrum świata (0,0,0)
    Cube cube {{-1.0, -1.0, -1.0}, {1.0, 1.0, 1.0}};

    // Zmienne kamery
    double angle = 0.0;   // Kąt obrotu wokół osi Y (w radianach)
    double radius = 6.0;  // Odległość kamery od środka (Zoom)

    // Ustawienia konsoli (rozdzielczość "ekranu" z literek)
    const int width = 60;  // Szerokość
    const int height = 30; // Wysokość

    // Korekta proporcji: Znak w konsoli jest prostokątem (wysoki, wąski).
    // Mnożymy szerokość przez 0.5, żeby koło wyglądało jak koło, a nie jajko.
    const double aspect_ratio = double(width) / height * 0.5;

    // Bufor: Tu składamy cały obrazek (napis) przed wyświetleniem, żeby nie migało.
    std::string screenBuffer;
    screenBuffer.reserve(width * height + height);

    while (true) {
        // --- KROK 1: Obliczanie pozycji kamery ---
        // Używamy trygonometrii, żeby kamera krążyła po okręgu
        double camX = std::sin(angle) * radius;
        double camZ = std::cos(angle) * radius;
        Vec3 cameraOrigin = {camX, 0.0, camZ};
        Vec3 target = {0, 0, 0}; // Kamera zawsze patrzy na środek (tam gdzie sześcian)

        // --- KROK 2: Budowanie układu współrzędnych kamery ---
        // Forward: Wektor patrzenia (od kamery do celu)
        Vec3 forward = (target - cameraOrigin).unit();

        // WorldUp: Wektor "Góra" w świecie (oś Y)
        Vec3 worldUp = {0, 1, 0};

        // Right: Wektor w prawo względem kamery (iloczyn wektorowy Forward i WorldUp)
        Vec3 right = forward.cross(worldUp).unit();

        // Up: Wektor w górę względem kamery (lokalne Y kamery)
        Vec3 up = right.cross(forward);

        // Przygotowanie bufora tekstowego
        screenBuffer = "";
        screenBuffer += "Sterowanie: a (lewo), d (prawo), w (zoom+), s (zoom-), q (wyjscie)\n";
        screenBuffer += "Po wpisaniu litery wcisnij ENTER.\n\n";

        // --- KROK 3: Ray Casting (Skanowanie pikseli) ---
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                // Zamiana współrzędnych piksela (x,y) na znormalizowane (u,v) od -1 do 1.
                // Dzięki temu (0,0) jest na środku ekranu.
                double u = (double(x) / width) * 2.0 - 1.0;
                double v = -((double(y) / height) * 2.0 - 1.0); // Minus, bo w konsoli Y rośnie w dół

                u *= aspect_ratio; // Naprawa proporcji (szerokość znaku)

                // Tworzenie promienia dla danego piksela:
                // Start + Kierunek (Forward + przesunięcie w prawo + przesunięcie w górę)
                Vec3 rayDir = (forward + (right * u) + (up * v)).unit();
                Ray r {cameraOrigin, rayDir};

                // Sprawdzenie kolizji
                if (cube.hit(r)) {
                    screenBuffer += "0"; // Trafienie w sześcian
                } else {
                    screenBuffer += "."; // Tło
                }
            }
            screenBuffer += '\n'; // Nowa linia po zakończeniu wiersza
        }

        // --- KROK 4: Wyświetlenie klatki ---
        clearScreen();           // "Wyczyść" poprzedni ekran
        std::cout << screenBuffer; // Wypisz nowy

        // --- KROK 5: Sterowanie ---
        std::cout << "> ";
        char cmd;
        std::cin >> cmd; // Czekamy na klawisz + Enter od użytkownika

        if (cmd == 'q') break;         // Wyjście
        if (cmd == 'a') angle -= 0.3;  // Obrót w lewo (zmniejsz kąt)
        if (cmd == 'd') angle += 0.3;  // Obrót w prawo (zwiększ kąt)
        if (cmd == 'w') radius -= 1.0; // Zoom in (zmniejsz dystans)
        if (cmd == 's') radius += 1.0; // Zoom out (zwiększ dystans)

        // Blokada, żeby nie wlecieć do środka sześcianu
        if (radius < 2.5) radius = 2.5;
    }

    return 0;
}