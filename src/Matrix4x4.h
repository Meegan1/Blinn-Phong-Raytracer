//
// Created by Jake Meegan on 01/12/2019.
//

#ifndef ASSIGNMENT_4_MATRIX4X4_H
#define ASSIGNMENT_4_MATRIX4X4_H


#ifndef ASSIGNMENT_3_VECTOR_H
#include "Vector.h"
#endif

class Matrix4x4 {
public:
    explicit Matrix4x4() = default;
    explicit Matrix4x4(float m[4][4]);

    Vector transform(const Vector &v);

    Matrix4x4 operator *(Matrix4x4 &m);
    Vector operator *(const Vector &v);
    float *operator [](int i);

private:
    float matrix[4][4] = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
    };
};


#endif //ASSIGNMENT_4_MATRIX4X4_H
