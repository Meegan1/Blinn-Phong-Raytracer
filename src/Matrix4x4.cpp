//
// Created by Jake Meegan on 01/12/2019.
//

#include "Matrix4x4.h"

Matrix4x4::Matrix4x4(float (*m)[4]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            matrix[i][j] = m[i][j];
        }
    }
}

Matrix4x4 Matrix4x4::operator*(Matrix4x4 &m) {
    Matrix4x4 c;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            c[i][j] = matrix[i][0] * m[0][j] + matrix[i][1] * m[1][j] +
                      matrix[i][2] * m[2][j] + matrix[i][3] * m[3][j];
        }
    }
    return c;
}

float *Matrix4x4::operator[](int i) {
    return matrix[i];
}

Vector Matrix4x4::operator*(const Vector &v) {

    float a, b, c, w;

    a = v.x * matrix[0][0] + v.y * matrix[1][0] + v.z * matrix[2][0] + matrix[3][0];
    b = v.x * matrix[0][1] + v.y * matrix[1][1] + v.z * matrix[2][1] + matrix[3][1];
    c = v.x * matrix[0][2] + v.y * matrix[1][2] + v.z * matrix[2][2] + matrix[3][2];
    w = v.x * matrix[0][3] + v.y * matrix[1][3] + v.z * matrix[2][3] + matrix[3][3];

    return {a/w, b/w, c/w};
}

Vector Matrix4x4::transform(const Vector &v) {
    float a, b, c;

    a = v.x * matrix[0][0] + v.y * matrix[1][0] + v.z * matrix[2][0];
    b = v.x * matrix[0][1] + v.y * matrix[1][1] + v.z * matrix[2][1];
    c = v.x * matrix[0][2] + v.y * matrix[1][2] + v.z * matrix[2][2];

    return {a, b, c};
};
