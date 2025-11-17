#include "Matrix4x4.h"

Matrix4x4::Matrix4x4() {
    for (int i = 0; i < 16; ++i) {
        entries[i] = 0;
    }
}

Matrix4x4::Matrix4x4(float e0, float e1, float e2, float e3,
    float e4, float e5, float e6, float e7,
    float e8, float e9, float e10, float e11,
    float e12, float e13, float e14, float e15) {
    entries[0] = e0; entries[1] = e1; entries[2] = e2; entries[3] = e3;
    entries[4] = e4; entries[5] = e5; entries[6] = e6; entries[7] = e7;
    entries[8] = e8; entries[9] = e9; entries[10] = e10; entries[11] = e11;
    entries[12] = e12; entries[13] = e13; entries[14] = e14; entries[15] = e15;
}

Matrix4x4::Matrix4x4(const Matrix4x4& mat) {
    memcpy(entries, mat.entries, sizeof(float) * 16);
}

Matrix4x4::Matrix4x4(const float* pf) {
    memcpy(entries, pf, sizeof(float) * 16);
}

Matrix4x4::~Matrix4x4() {}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& mat) const {
    return Matrix4x4(entries[0] + mat.entries[0], entries[1] + mat.entries[1],
        entries[2] + mat.entries[2], entries[3] + mat.entries[3],
        entries[4] + mat.entries[4], entries[5] + mat.entries[5],
        entries[6] + mat.entries[6], entries[7] + mat.entries[7],
        entries[8] + mat.entries[8], entries[9] + mat.entries[9],
        entries[10] + mat.entries[10], entries[11] + mat.entries[11],
        entries[12] + mat.entries[12], entries[13] + mat.entries[13],
        entries[14] + mat.entries[14], entries[15] + mat.entries[15]);
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& mat) const {
    return Matrix4x4(entries[0] - mat.entries[0], entries[1] - mat.entries[1],
        entries[2] - mat.entries[2], entries[3] - mat.entries[3],
        entries[4] - mat.entries[4], entries[5] - mat.entries[5],
        entries[6] - mat.entries[6], entries[7] - mat.entries[7],
        entries[8] - mat.entries[8], entries[9] - mat.entries[9],
        entries[10] - mat.entries[10], entries[11] - mat.entries[11],
        entries[12] - mat.entries[12], entries[13] - mat.entries[13],
        entries[14] - mat.entries[14], entries[15] - mat.entries[15]);
}

Matrix4x4 Matrix4x4::operator*(const float f) const {
    return Matrix4x4(entries[0] * f, entries[1] * f, entries[2] * f, entries[3] * f,
        entries[4] * f, entries[5] * f, entries[6] * f, entries[7] * f,
        entries[8] * f, entries[9] * f, entries[10] * f, entries[11] * f,
        entries[12] * f, entries[13] * f, entries[14] * f, entries[15] * f);
}

Vector4 Matrix4x4::operator*(const Vector4& v) const {
    float resultX = entries[0] * v.x + entries[4] * v.y + entries[8] * v.z + entries[12] * v.w;
    float resultY = entries[1] * v.x + entries[5] * v.y + entries[9] * v.z + entries[13] * v.w;
    float resultZ = entries[2] * v.x + entries[6] * v.y + entries[10] * v.z + entries[14] * v.w;
    float resultW = entries[3] * v.x + entries[7] * v.y + entries[11] * v.z + entries[15] * v.w;
    return Vector4(resultX, resultY, resultZ, resultW);
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& mat) const {
    Matrix4x4 result;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            result.entries[row * 4 + col] =
                entries[row * 4 + 0] * mat.entries[0 * 4 + col] +
                entries[row * 4 + 1] * mat.entries[1 * 4 + col] +
                entries[row * 4 + 2] * mat.entries[2 * 4 + col] +
                entries[row * 4 + 3] * mat.entries[3 * 4 + col];
        }
    }
    return result;
}

bool Matrix4x4::operator==(const Matrix4x4& mat) const {
    for (int i = 0; i < 16; ++i) {
        if (entries[i] != mat.entries[i]) return false;
    }
    return true;
}

bool Matrix4x4::operator!=(const Matrix4x4& mat) const {
    return !(*this == mat);
}

void Matrix4x4::LoadIdentity(void) {
    memset(entries, 0, 16 * sizeof(float));
    entries[0] = 1.0f; entries[5] = 1.0f; entries[10] = 1.0f; entries[15] = 1.0f;
}

void Matrix4x4::print() const {
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            std::cout << entries[r * 4 + c] << " ";
        }
        std::cout << std::endl;
    }
}

void Matrix4x4::setMatrixAsInverseOfGivenMatrix(const Matrix4x4& m) {
    float t1 = m.entries[0] * m.entries[0];
    float t2 = m.entries[6] * m.entries[7];
    float t3 = m.entries[3] * m.entries[1];
    float t4 = m.entries[8] * m.entries[1];
    float t5 = m.entries[9] * m.entries[2];
    float t6 = m.entries[2] * m.entries[2];
    float det = (t1 - m.entries[8] - t2) * m.entries[5] - t3 * m.entries[7] + t4 * m.entries[5] + t5 * m.entries[7] - t6 * m.entries[4];
    if (det == 0.0) return;
    float invd = 1.0f / det;
    float m0 = (m.entries[4] * m.entries[8] - m.entries[7] * m.entries[5]) * invd;
    float m3 = -(m.entries[3] * m.entries[8] - m.entries[6] * m.entries[5]) * invd;
    float m6 = (m.entries[3] * m.entries[7] - m.entries[6] * m.entries[4]) * invd;
    float m1 = -(m.entries[1] * m.entries[8] - m.entries[7] * m.entries[2]) * invd;
    float m4 = (m.entries[0] * m.entries[8] - t2 - t4) * invd;
    float m7 = -(t2 - t4) * invd;
    float m2 = (m.entries[1] * m.entries[5] - m.entries[4] * m.entries[2]) * invd;
    float m5 = -(m.entries[0] * m.entries[5] - t3 - t5) * invd;
    float m8 = 0 - (t1 - t3) * invd;
    entries[0] = m0; entries[3] = m3; entries[6] = m6;
    entries[1] = m1; entries[4] = m4; entries[7] = m7;
    entries[2] = m2; entries[5] = m5; entries[8] = m8;
}

Matrix4x4 Matrix4x4::getInverseOfMatrix() const {
    Matrix4x4 result;
    result.setMatrixAsInverseOfGivenMatrix(*this);
    return result;
}

void Matrix4x4::invertMatrix() {
    setMatrixAsInverseOfGivenMatrix(*this);
}

void Matrix4x4::setMatrixAsTransposeOfGivenMatrix(const Matrix4x4& m) {
    entries[0] = m.entries[0]; entries[3] = m.entries[1]; entries[6] = m.entries[2];
    entries[1] = m.entries[3]; entries[4] = m.entries[4]; entries[7] = m.entries[5];
    entries[2] = m.entries[6]; entries[5] = m.entries[7]; entries[8] = m.entries[8];
}

Matrix4x4 Matrix4x4::getTransposeOfMatrix() const {
    Matrix4x4 result;
    result.setMatrixAsTransposeOfGivenMatrix(*this);
    return result;
}

void Matrix4x4::SetTranslationPart(const Vector3& translation) {
    entries[12] = translation.x;
    entries[13] = translation.y;
    entries[14] = translation.z;
}

void Matrix4x4::SetScale(const Vector3& scaleFactor) {
    LoadIdentity();
    entries[0] = scaleFactor.x;
    entries[5] = scaleFactor.y;
    entries[10] = scaleFactor.z;
}

void Matrix4x4::SetUniformScale(const float scaleFactor) {
    LoadIdentity();
    entries[0] = entries[5] = entries[10] = scaleFactor;
}

void Matrix4x4::SetRotationAxis(const double angle, Vector3& axis) {
    axis.normalize();
    Vector3 u(axis);
    float sinAngle = (float)sin(M_PI * angle / 180);
    float cosAngle = (float)cos(M_PI * angle / 180);
    float oneMinusCosAngle = 1.0f - cosAngle;
    LoadIdentity();
    entries[0] = (u.x) * (u.x) + cosAngle * (1 - (u.x) * (u.x));
    entries[4] = (u.x) * (u.y) * (oneMinusCosAngle)-sinAngle * u.z;
    entries[8] = (u.x) * (u.z) * (oneMinusCosAngle)+sinAngle * u.y;
    entries[1] = (u.x) * (u.y) * (oneMinusCosAngle)+sinAngle * u.z;
    entries[5] = (u.y) * (u.y) + cosAngle * (1 - (u.y) * (u.y));
    entries[9] = (u.y) * (u.z) * (oneMinusCosAngle)-sinAngle * u.x;
    entries[2] = (u.x) * (u.z) * (oneMinusCosAngle)-sinAngle * u.y;
    entries[6] = (u.y) * (u.z) * (oneMinusCosAngle)+sinAngle * u.x;
    entries[10] = (u.z) * (u.z) + cosAngle * (1 - (u.z) * (u.z));
}

void Matrix4x4::SetRotationX(const double angle) {
    LoadIdentity();
    entries[5] = (float)cos(M_PI * angle / 180);
    entries[6] = (float)sin(M_PI * angle / 180);
    entries[9] = -entries[6];
    entries[10] = entries[5];
}

void Matrix4x4::SetRotationY(const double angle) {
    LoadIdentity();
    entries[0] = (float)cos(M_PI * angle / 180);
    entries[2] = -(float)sin(M_PI * angle / 180);
    entries[8] = -entries[2];
    entries[10] = entries[0];
}

void Matrix4x4::SetRotationZ(const double angle) {
    LoadIdentity();
    entries[0] = (float)cos(M_PI * angle / 180);
    entries[1] = (float)sin(M_PI * angle / 180);
    entries[4] = -entries[1];
    entries[5] = entries[0];
}