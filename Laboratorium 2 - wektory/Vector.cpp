#include "Vector.h"

using namespace std;

Vector::Vector() : x(0), y(0), z(0) {}

Vector::Vector(float x, float y, float z) : x(x), y(y), z(z) {}

Vector::Vector(const Vector& v) : x(v.x), y(v.y), z(v.z) {}

Vector::~Vector() {}

void Vector::operator+=(const Vector& v) {
    x += v.x;
    y += v.y;
    z += v.z;
}

void Vector::operator-=(const Vector& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

void Vector::div(float f) {
    if (f != 0) {
        x /= f;
        y /= f;
        z /= f;
    }
    else
        cout << "Cannot divide by zero!" << endl;
}

void Vector::mag(float f) {
    x *= f;
    y *= f;
    z *= f;
}

float Vector::length() {
    return sqrt(x * x + y * y + z * z);
}

void Vector::normalize() {
    float n = this->length();
    if (n != 0) {
        this->div(n);
    }
    else
        cout << "Cannot divide by 0" << endl;
}

Vector Vector::dot(Vector v) {
    Vector result;
    result.x = this->x * v.x;
    result.y = this->y * v.y;
    result.z = this->z * v.z;
    return result;
}

float Vector::dotProduct(Vector v) {
    Vector result;
    result.x = this->x * v.x;
    result.y = this->y * v.y;
    result.z = this->z * v.z;
    return result.x + result.y + result.z;
}

Vector Vector::cross(Vector v) {
    return Vector(
        this->y * v.z - this->z * v.y,
        this->z * v.x - this->x * v.z,
        this->x * v.y - this->y * v.x);
}

void Vector::print(const std::string& name) const {
    std::cout << (name.empty() ? "Vector" : name)
        << " (" << x << ", " << y << ", " << z << ")\n";
}