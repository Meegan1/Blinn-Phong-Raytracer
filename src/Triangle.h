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
    Vector ambient{}, specular{}, diffuse{}, emission{};
    float specular_coefficient;

    Triangle(Vertex A, Vertex B, Vertex C) : A(A), B(B), C(C) {}

    Triangle(Vertex a, Vertex b, Vertex c, Vector ambient, Vector diffuse, Vector specular, float specular_coefficient)
            : A(a),
              B(b),
              C(c),
              ambient(ambient),
              diffuse(diffuse),
              specular(specular),
              specular_coefficient(specular_coefficient) {}

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

    Vector normal() {
        return (B.position - A.position).cross((C.position - A.position)).normalize();
    }
};

struct Surfel {
    Triangle *triangle;
    Vector location;
    float alpha, beta, gamma;
    Vector normal;
    bool reflects_direct = true, scatterImpulse, emits;

    Surfel(Triangle *triangle, const Vector &location, float alpha, float beta, float gamma) : triangle(triangle),
                                                                                               location(location),
                                                                                               alpha(alpha), beta(beta),
                                                                                               gamma(gamma) {
        normal = triangle->normal();
    }

    Vector BSDF(Vector incident, Vector reflection) {
        RGB color =  (triangle->A.color * alpha) + (triangle->B.color * beta) + (triangle->C.color * gamma);
        return color;
    }

    Vector getImpulseDirection(const Vector &ray) {
        return {1};
    }

    float extinction_probability() {
        return 100;
    }
};


#endif //ASSIGNMENT_3_TRIANGLE_H
