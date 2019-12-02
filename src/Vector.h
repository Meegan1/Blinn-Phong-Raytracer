//
// Created by Jake Meegan on 28/11/2019.
//



#ifndef ASSIGNMENT_3_VECTOR_H
#define ASSIGNMENT_3_VECTOR_H

#endif //ASSIGNMENT_3_VECTOR_H

#include "cmath"

typedef float Position;

/*
 * Struct for Vector
 */
struct Vector {
    Position x, y, z;
    Vector(Position x, Position y, Position z) : x(x), y(y), z(z) {}

    Vector operator - (const Vector &other) {
        return {x - other.x, y - other.y, z - other.z};
    }
    Vector operator - (float other) {
        return {x - other, y - other, z - other};
    }
    
    Vector operator + (const Vector &other) {
        return {x + other.x, y + other.y, z + other.z};
    }
    Vector operator + (float other) {
        return {x + other, y + other, z + other};
    }

    Vector operator * (const Vector &other) {
        return {x * other.x, y * other.y, z * other.z};
    }

    Vector operator * (float other) {
        return {x * other, y * other, z * other};
    }

    Vector operator / (float num) {
        return {x/num, y/num, z/num};
    }

    float magnitude() {
        return sqrt((x * x) + (y * y) + (z * z));
    }

    Vector normalize() {
        return this->operator/(magnitude());
    }

    float dot(const Vector &other) {
        return (x*other.x) + (y*other.y) + (z*other.z);
    }

    Vector cross(const Vector &other) {
        return {(y * other.z) - (z * other.y), (z * other.x) - (x * other.z), (x * other.y) - (y * other.x)};
    }
};