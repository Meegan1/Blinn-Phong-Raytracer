//
// Created by Jake Meegan on 19/12/2019.
//

#ifndef ASSIGNMENT_4_COLOR_H
#define ASSIGNMENT_4_COLOR_H

#include "Vertex.h"

#define SCREEN_GAMMA 2.2f


class Color {
public:
    static RGB correct(RGB color) {
        return color.pow(1/SCREEN_GAMMA);
    }
};


#endif //ASSIGNMENT_4_COLOR_H
