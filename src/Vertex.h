//
// Created by Jake Meegan on 16/11/2019.
//

#include "Vector.h"

#ifndef ASSIGNMENT_3_VERTEX_H
#define ASSIGNMENT_3_VERTEX_H

#endif //ASSIGNMENT_3_VERTEX_H

/*
 * Typedefs
 */
typedef unsigned char Color;
typedef float Position;

/*
 * Struct for RGB (Colours)
 */
struct RGB {
    Color r, g, b;

    RGB() = default;

    RGB(Color r, Color g, Color b) : r(r), g(g), b(b) {}
};

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

    Vertex(Vector position, RGB color, UV uv) : position(position), color(color), uv(uv) {}
};
