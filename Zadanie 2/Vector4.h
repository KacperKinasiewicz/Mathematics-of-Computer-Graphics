#pragma once
#include <cmath>
#include <iostream>
#include <string>

class Vector4 {
public:
    float x, y, z, w;
    Vector4(float x, float y, float z, float w);
    ~Vector4();
    void print(const std::string& name = "") const;
};