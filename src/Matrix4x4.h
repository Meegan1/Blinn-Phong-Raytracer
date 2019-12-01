//
// Created by Jake Meegan on 01/12/2019.
//

#ifndef ASSIGNMENT_4_MATRIX4X4_H
#define ASSIGNMENT_4_MATRIX4X4_H


class Matrix4x4 {
    float matrix[4][4] = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
    };

    explicit Matrix4x4(float m[4][4]);
};


#endif //ASSIGNMENT_4_MATRIX4X4_H
