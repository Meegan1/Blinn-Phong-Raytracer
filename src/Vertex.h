//
// Created by Jake Meegan on 16/11/2019.
//



#ifndef ASSIGNMENT_3_VERTEX_H
#define ASSIGNMENT_3_VERTEX_H

#include "Vector.h"

/*
 * Typedefs
 */
typedef float Position;
typedef Vector RGB;


/*
 * Struct for UV texture mapping coords
 */
struct UV {
    float u, v;
    UV(float u, float v) : u(u), v(v) {}
};

/*
 * Struct for Vertex
 */
struct Vertex {
    Vector position;
    RGB color;
    UV uv;

    Vertex(Vector position, RGB color, UV uv) : position(position), color(color.RGBToVector()), uv(uv) {}
};

#endif //ASSIGNMENT_3_VERTEX_H
