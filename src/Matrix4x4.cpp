//
// Created by Jake Meegan on 01/12/2019.
//

#include "Matrix4x4.h"

Matrix4x4::Matrix4x4(float (*m)[4]) {
    for(int r = 0; r < 4; r++) {
        for(int c = 0; c < 4; c++) {
            matrix[r][c] = m[r][c];
        }
    }
}
