//
// Created by Jake Meegan on 16/11/2019.
//

#ifndef ASSIGNMENT_3_TRIANGLE_H
#define ASSIGNMENT_3_TRIANGLE_H

#include "Vertex.h"

/*
 * Struct for Triangle
 */
struct Triangle {
    Vertex A, B, C;
    Vector ambient{}, specular{}, diffuse{};
    float diffuse_reflectivity;

    Triangle(Vertex A, Vertex B, Vertex C) : A(A), B(B), C(C) {}

    Triangle(Vertex a, Vertex b, Vertex c, Vector ambient, Vector specular, Vector diffuse, float diffuse_reflectivity)
            : A(a),
              B(b),
              C(c),
              ambient(ambient),
              specular(specular),
              diffuse(diffuse),
              diffuse_reflectivity(diffuse_reflectivity) {}

    // Get barycentric co-ordinates at point p, from vertices [A, B, C]
    void get_barycentric(Vector p, float &alpha, float &beta, float &gamma) {
        Vector a = A.position;
        Vector b = B.position;
        Vector c = C.position;

        float den = ((b.y - c.y)*(a.x - c.x)) + ((c.x - b.x) * (a.y - c.y));

        alpha = (((b.y - c.y)*(p.x - c.x)) + ((c.x - b.x) * (p.y - c.y))) / den;
        beta = (((c.y - a.y) * (p.x - c.x)) + ((a.x - c.x) * (p.y - c.y))) / den;
        gamma = 1.0f - alpha - beta;
    }
};


#endif //ASSIGNMENT_3_TRIANGLE_H
