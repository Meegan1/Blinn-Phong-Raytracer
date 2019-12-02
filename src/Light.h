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
    float ambient, specular, diffuse;

    Light(Vector position, Vector direction, float ambient, float specular, float diffuse) : position(position), direction(direction),
                                                                              ambient(ambient), specular(specular), diffuse(diffuse) {}
};


#endif //ASSIGNMENT_4_LIGHT_H
