#include "Vector4.h"

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
Vector4::~Vector4() {}
void Vector4::print(const std::string& name) const {
    std::cout << (name.empty() ? "Vector4" : name)
        << " (" << x << ", " << y << ", " << z << ", " << w << ")\n";
}