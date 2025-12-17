#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

struct Vec3 {
    double x, y, z;

    Vec3 operator+(const Vec3& v) const { return {x + v.x, y + v.y, z + v.z}; }

    Vec3 operator-(const Vec3& v) const { return {x - v.x, y - v.y, z - v.z}; }

    Vec3 operator*(double t) const { return {x * t, y * t, z * t}; }

    double dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }

    Vec3 cross(const Vec3& v) const {
        return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
    }

    Vec3 unit() const {
        double len = std::sqrt(x*x + y*y + z*z);
        return (len > 0) ? Vec3{x/len, y/len, z/len} : Vec3{0,0,0};
    }
};

struct Ray {
    Vec3 origin;
    Vec3 direction;
};

struct Cube {
    Vec3 minBound;
    Vec3 maxBound;

    bool hit(const Ray& r) const {
        double t_min = 0.0;
        double t_max = 100000.0;

        if (std::abs(r.direction.x) < 1e-5) {
             if (r.origin.x < minBound.x || r.origin.x > maxBound.x) return false;
        } else {
            double invD = 1.0 / r.direction.x;
            double t0 = (minBound.x - r.origin.x) * invD;
            double t1 = (maxBound.x - r.origin.x) * invD;

            if (t0 > t1) std::swap(t0, t1);

            t_min = std::max(t_min, t0);
            t_max = std::min(t_max, t1);

            if (t_min > t_max) return false;
        }

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

        return true;
    }
};

void clearScreen() {
    for(int i=0; i<50; i++) std::cout << "\n";
}

int main() {
    Cube cube {{-1.0, -1.0, -1.0}, {1.0, 1.0, 1.0}};

    double angle = 0.0;
    double radius = 6.0;

    const int width = 60;
    const int height = 30;

    const double aspect_ratio = double(width) / height * 0.5;

    std::string screenBuffer;
    screenBuffer.reserve(width * height + height);

    while (true) {
        double camX = std::sin(angle) * radius;
        double camZ = std::cos(angle) * radius;
        Vec3 cameraOrigin = {camX, 0.0, camZ};
        Vec3 target = {0, 0, 0};

        Vec3 forward = (target - cameraOrigin).unit();

        Vec3 worldUp = {0, 1, 0};

        Vec3 right = forward.cross(worldUp).unit();

        Vec3 up = right.cross(forward);

        screenBuffer = "";
        screenBuffer += "Sterowanie: a (lewo), d (prawo), w (zoom+), s (zoom-), q (wyjscie)\n";
        screenBuffer += "Po wpisaniu litery wcisnij ENTER.\n\n";

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                double u = (double(x) / width) * 2.0 - 1.0;
                double v = -((double(y) / height) * 2.0 - 1.0);

                u *= aspect_ratio;

                Vec3 rayDir = (forward + (right * u) + (up * v)).unit();
                Ray r {cameraOrigin, rayDir};

                if (cube.hit(r)) {
                    screenBuffer += "0";
                } else {
                    screenBuffer += ".";
                }
            }
            screenBuffer += '\n';
        }

        clearScreen();
        std::cout << screenBuffer;

        std::cout << "> ";
        char cmd;
        std::cin >> cmd;

        if (cmd == 'q') break;
        if (cmd == 'a') angle -= 0.3;
        if (cmd == 'd') angle += 0.3;
        if (cmd == 'w') radius -= 1.0;
        if (cmd == 's') radius += 1.0;

        if (radius < 2.5) radius = 2.5;
    }

    return 0;
}