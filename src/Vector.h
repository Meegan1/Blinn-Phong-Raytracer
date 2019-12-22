//
// Created by Jake Meegan on 28/11/2019.
//



#ifndef ASSIGNMENT_3_VECTOR_H
#define ASSIGNMENT_3_VECTOR_H

#include "cmath"
#include "Vertex.h"

typedef float Position;

/*
 * Struct for Vector
 */
struct Vector {
    union{Position x; float r;};
    union{Position y; float g;};
    union{Position z; float b;};

    Vector() : x(0), y(0), z(0) {}
    Vector(Position x, Position y, Position z) : x(x), y(y), z(z) {}
    Vector(Position value) : x(value), y(value), z(value) {}

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

    Vector & operator += (const Vector & other) {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }

    Vector & operator += (const float & num) {
        this->x += num;
        this->y += num;
        this->z += num;
        return *this;
    }

    Vector operator - () {
        return {-x, -y, -z};
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

    Vector pow(float num) {
        return {std::pow(x, num), std::pow(y, num), std::pow(z, num)};
    }

    Vector toRGB() {
        return {x * 255, y * 255, z * 255};
    }

    Vector RGBToVector() {
        return {x / 255, y / 255, z / 255};
    }

    static void createCoordinateSystem(Vector normal, Vector &right, Vector &up) {
        if(abs(normal.x) > abs(normal.y))
            right = Vector(normal.z, 0, normal.x).normalize();
        else
            right = Vector(0, -normal.z, normal.y);

        up = normal.cross(right);
    }

    static Vector sampleHemisphere(const float &u, const float &v) {
        float x = cosf(2 * M_PI * u);
        float z = sinf(2 * M_PI * v);
        return {x, v, z};
    }
};

#endif //ASSIGNMENT_3_VECTOR_H