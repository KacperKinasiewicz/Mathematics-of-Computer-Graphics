#ifndef MAT2_MATRIX4X4_H
#define MAT2_MATRIX4X4_H
#define _USE_MATH_DEFINES
#include "Vector3.h"
#include "Vector4.h"

class Matrix4x4 {
public:
    float entries[16];

    Matrix4x4();
    Matrix4x4(float e0, float e1, float e2, float e3,
              float e4, float e5, float e6, float e7,
              float e8, float e9, float e10, float e11,
              float e12, float e13, float e14, float e15);
    Matrix4x4(const float * f);
    Matrix4x4(const Matrix4x4 &mat);
    ~Matrix4x4();
    Matrix4x4 operator+(const Matrix4x4 &mat) const;
    Matrix4x4 operator-(const Matrix4x4 &mat) const;
    Matrix4x4 operator*(const float f) const;
    Matrix4x4 operator*(const Matrix4x4 &mat) const;
    bool operator==(const Matrix4x4& mat) const;
    bool operator!=(const Matrix4x4& mat) const;
    void LoadIdentity(void);
    Matrix4x4 getInverseOfMatrix() const;
    Matrix4x4 getTransposeOfMatrix() const;
    void invertMatrix();
    void print() const;
    void setMatrixAsInverseOfGivenMatrix(const Matrix4x4 &);
    void setMatrixAsTransposeOfGivenMatrix(const Matrix4x4 &m);
    void SetTranslationPart(const Vector3 &translation);

    void SetScale(const Vector3 &scaleFactor);
    void SetUniformScale(float scaleFactor);

    void SetRotationAxis(double angle, Vector3 &axis);

    void SetRotationX(double angle);

    void SetRotationY(double angle);

    void SetRotationZ(double angle);

    Vector4 operator*(const Vector4 &v) const;
};

#endif //MAT2_MATRIX4X4_H