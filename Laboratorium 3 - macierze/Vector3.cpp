#include "Vector3.h"

using namespace std;

Vector3::Vector3() : x(0), y(0), z(0) {}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3::Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}

Vector3::~Vector3() {}

void Vector3::operator+=(const Vector3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
}

void Vector3::operator-=(const Vector3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

void Vector3::div(float f) {
    if (f != 0) {
        x /= f;
        y /= f;
        z /= f;
    }
    else
        cout << "Cannot divide by zero!" << endl;
}

void Vector3::mag(float f) {
    x *= f;
    y *= f;
    z *= f;
}

float Vector3::length() {
    return sqrt(x * x + y * y + z * z);
}

void Vector3::normalize() {
    float n = this->length();
    if (n != 0) {
        this->div(n);
    }
    else
        cout << "Cannot divide by 0" << endl;
}

Vector3 Vector3::dot(Vector3 v) {
    Vector3 result;
    result.x = this->x * v.x;
    result.y = this->y * v.y;
    result.z = this->z * v.z;
    return result;
}

float Vector3::dotProduct(Vector3 v) {
    Vector3 result;
    result.x = this->x * v.x;
    result.y = this->y * v.y;
    result.z = this->z * v.z;
    return result.x + result.y + result.z;
}

Vector3 Vector3::cross(Vector3 v) {
    return Vector3(
        this->y * v.z - this->z * v.y,
        this->z * v.x - this->x * v.z,
        this->x * v.y - this->y * v.x);
}

void Vector3::print(const std::string& name) const {
    std::cout << (name.empty() ? "Vector3" : name)
        << " (" << x << ", " << y << ", " << z << ")\n";
}