//
// Created by Jake Meegan on 02/12/2019.
//

#ifndef ASSIGNMENT_4_LIGHT_H
#define ASSIGNMENT_4_LIGHT_H

#include "Vector.h"

class Light {
public:
    Vector position;
    Vector direction;
    Vector ambient, specular;
    float specular_coefficient;

    Light(Vector position, Vector direction, Vector ambient, Vector specular, float specular_coefficient)
            : position(position), direction(direction.normalize()),
              ambient(ambient), specular(specular),
              specular_coefficient(specular_coefficient) {}
};


#endif //ASSIGNMENT_4_LIGHT_H
