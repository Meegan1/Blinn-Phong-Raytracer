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
    Vector color;
    Vector ambient, diffuse, specular;

    Light(Vector position, Vector direction, Vector ambient)
            : position(position), direction(direction.normalize()),
              ambient(ambient), color(1) {}

    Light(Vector position, Vector direction, Vector color, Vector ambient) : position(
            position), direction(direction.normalize()), ambient(ambient), color(color) {}


    RGB computeAmbient(Triangle &surface, RGB &color) {
        return color * (this->ambient * surface.ambient);
    }

    RGB computeDiffuse(Triangle &surface, Vector &normal, RGB &surface_color, Vector &point) {
        float diffuse_angle = std::fmax(normal.dot((point - this->position).normalize()), 0.0f);
        float distance = (this->position - point).magnitude();
        float inverse_square = 1 / (distance * distance);

        return (color * surface_color * (surface.diffuse * diffuse_angle)) * inverse_square;
    }

    RGB computeSpecular(Triangle &surface, Vector &normal, Vector &point, Vector &ray_direction) {
        Vector halfDirection = (((point - this->position).normalize() + ray_direction) / 2).normalize();
        float specular_angle = halfDirection.dot(normal);
        float distance = (this->position - point).magnitude();
        float inverse_square = 1 / (distance * distance);

        return color * surface.specular * pow(specular_angle, surface.specular_coefficient)*inverse_square;
    }
};


#endif //ASSIGNMENT_4_LIGHT_H
