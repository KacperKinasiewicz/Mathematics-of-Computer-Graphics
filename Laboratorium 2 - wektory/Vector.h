#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>

class Vector {
public:
    float x, y, z;

    Vector();
    Vector(float x, float y, float z);
    ~Vector();
    Vector(const Vector& v);
    void operator+=(const Vector& v);
    void operator-=(const Vector& v);
    void div(float f);
    void mag(float f);
    float length();
    void normalize();
    Vector dot(Vector v);
    float dotProduct(Vector v);
    Vector cross(Vector v);
    void print(const std::string& name = "") const;
};