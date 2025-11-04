#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>

class Vector3 {
public:
    float x, y, z;

    Vector3();
    Vector3(float x, float y, float z);
    ~Vector3();
    Vector3(const Vector3& v);
    void operator+=(const Vector3& v);
    void operator-=(const Vector3& v);
    void div(float f);
    void mag(float f);
    float length();
    void normalize();
    Vector3 dot(Vector3 v);
    float dotProduct(Vector3 v);
    Vector3 cross(Vector3 v);
    void print(const std::string& name = "") const;
};