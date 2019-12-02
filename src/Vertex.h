//
// Created by Jake Meegan on 16/11/2019.
//



#ifndef ASSIGNMENT_3_VERTEX_H
#define ASSIGNMENT_3_VERTEX_H
#endif //ASSIGNMENT_3_VERTEX_H

#ifndef ASSIGNMENT_3_VECTOR_H
#include "Vector.h"
#endif

/*
 * Typedefs
 */
typedef int Color;
typedef float Position;

/*
 * Struct for RGB (Colours)
 */
struct RGB {
    Color r, g, b;

    RGB() = default;

    RGB(Color r, Color g, Color b) : r(r), g(g), b(b) {}

    RGB operator * (float num) { return {static_cast<Color>(r*num), static_cast<Color>(g*num), static_cast<Color>(b*num)}; }
    RGB operator / (float num) { return {static_cast<Color>(r/num), static_cast<Color>(g/num), static_cast<Color>(b/num)}; }
    RGB operator + (float num) { return {static_cast<Color>(r+num), static_cast<Color>(g+num), static_cast<Color>(b+num)}; }
    RGB operator + (const RGB &color) { return {static_cast<Color>(r+color.r), static_cast<Color>(g+color.g), static_cast<Color>(b+color.b)}; }
    RGB operator - (float num) { return {static_cast<Color>(r-num), static_cast<Color>(g-num), static_cast<Color>(b-num)}; }
    RGB operator - (const RGB &color) { return {static_cast<Color>(r-color.r), static_cast<Color>(g-color.g), static_cast<Color>(b-color.b)}; }
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
