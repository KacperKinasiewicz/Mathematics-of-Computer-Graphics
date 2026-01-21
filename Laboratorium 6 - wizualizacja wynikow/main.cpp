#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>

struct Vec3 {
    double x, y, z;

    Vec3 operator+(const Vec3& v) const { return {x + v.x, y + v.y, z + v.z}; }
    Vec3 operator*(double t) const { return {x * t, y * t, z * t}; }

    // iloczyn wektorowy do ustawienia osi kamery (wektory prostopadle)
    Vec3 cross(const Vec3& v) const {
        return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
    }

    Vec3 normalize() const {
        double len = std::sqrt(x * x + y * y + z * z);
        return (len > 0) ? Vec3{x / len, y / len, z / len} : Vec3{0, 0, 0};
    }
};

struct Ray {
    Vec3 origin;
    Vec3 direction;
};

struct Cube {
    Vec3 minBound;
    Vec3 maxBound;

    // sprawdzanie czy promien trafil w boxa (metoda slab)
    bool intersect(const Ray& r) const {
        double tMin = 0.0;
        double tMax = 100000.0;

        double p[] = {r.origin.x, r.origin.y, r.origin.z};
        double d[] = {r.direction.x, r.direction.y, r.direction.z};
        double bMin[] = {minBound.x, minBound.y, minBound.z};
        double bMax[] = {maxBound.x, maxBound.y, maxBound.z};

        for (int i = 0; i < 3; ++i) {
            double invD = 1.0 / d[i];
            double t0 = (bMin[i] - p[i]) * invD;
            double t1 = (bMax[i] - p[i]) * invD;

            if (invD < 0.0) std::swap(t0, t1);

            // szukanie czesci wspolnej przedzialow dla kazdej osi
            tMin = std::max(tMin, t0);
            tMax = std::min(tMax, t1);

            if (tMax <= tMin) return false; // jak sie nie przecinaja to pudlo
        }
        return true;
    }
};

void clearScreen() {
    for (int i = 0; i < 50; i++) std::cout << "\n";
}

int main() {
    Cube cube{{-1.0, -1.0, -1.0}, {1.0, 1.0, 1.0}};

    double yaw = 0.0;
    double pitch = 0.0;
    double radius = 6.0;

    const double step = M_PI / 16.0;
    const int width = 60;
    const int height = 30;
    const double aspectRatio = (double)width / height * 0.5;

    std::string buffer;
    buffer.reserve(width * height + height + 256);

    while (true) {
        // przeliczanie katow na pozycje kamery (wspolrzedne sferyczne)
        double camX = radius * std::cos(pitch) * std::sin(yaw);
        double camY = radius * std::sin(pitch);
        double camZ = radius * std::cos(pitch) * std::cos(yaw);
        Vec3 cameraPos = {camX, camY, camZ};

        // kierunek "patrzenia" kamery na srodek ukladu
        Vec3 forward = (cameraPos * -1.0).normalize();
        Vec3 worldUp = {0, 1, 0};

        // fix na gimbal locka przy patrzeniu pionowo
        if (std::abs(std::cos(pitch)) < 0.001) worldUp = {0, 0, 1};

        // osie lokalne kamery (prawo i gora)
        Vec3 right = forward.cross(worldUp).normalize();
        Vec3 up = right.cross(forward);

        buffer = "";
        buffer += "STEROWANIE: W/S, A/D, Z/X (Zoom), Q (Wyjscie)\n";
        buffer += "-----------------------------------------------------------------------\n";

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                // mapowanie pikseli na zakres -1 do 1 (z uwzglednieniem proporcji)
                double u = (((double)x / width) * 2.0 - 1.0) * aspectRatio;
                double v = -(((double)y / height) * 2.0 - 1.0);

                // kierunek promienia dla danego znaku w konsoli
                Vec3 rayDir = (forward + (right * u) + (up * v)).normalize();

                if (cube.intersect({cameraPos, rayDir})) {
                    buffer += "0";
                } else {
                    buffer += ".";
                }
            }
            buffer += '\n';
        }

        clearScreen();
        std::cout << buffer;
        std::cout.flush();

        std::cout << "> ";
        char input;
        std::cin >> input;

        if (input == 'q') break;

        // prosta obsluga klawiszy do obracania
        if (input == 'a') yaw -= step;
        if (input == 'd') yaw += step;
        if (input == 'w') pitch += step;
        if (input == 's') pitch -= step;
        if (input == 'z') radius -= 1.0;
        if (input == 'x') radius += 1.0;

        if (radius < 2.5) radius = 2.5;
    }

    return 0;
}