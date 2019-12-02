//
// Created by Jake Meegan on 02/12/2019.
//

#ifndef ASSIGNMENT_4_LIGHT_H
#define ASSIGNMENT_4_LIGHT_H

#ifndef ASSIGNMENT_3_VECTOR_H
#include "Vector.h"
#endif

class Light {
public:
    Vector position;
    Vector direction;

    Light(Vector position, Vector direction) : position(position), direction(direction) {}
};


#endif //ASSIGNMENT_4_LIGHT_H
