//
// Created by Jake Meegan on 16/11/2019.
//

#ifndef ASSIGNMENT_3_TRIANGLE_H
#define ASSIGNMENT_3_TRIANGLE_H

#include <cstdlib>
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
    Vector impulse{0};
    bool reflects_direct, scatterImpulse = true, emits;

    Surfel(Triangle *triangle, const Vector &location, float alpha, float beta, float gamma) : triangle(triangle),
                                                                                               location(location),
                                                                                               alpha(alpha), beta(beta),
                                                                                               gamma(gamma) {
        if(triangle != nullptr) {
            normal = triangle->normal();
            impulse = triangle->specular;
        }
    }

    Vector BSDF(Vector incident, Vector reflection) {
        return color();
    }

    Vector getImpulseDirection(Vector &ray) {
        Vector r = (normal * (2 * (ray.dot(normal)))) - ray;
        return r;
    }

    float extinction_probability() {
        return 1000;
    }

    Vector color() {
        return {(triangle->A.color * alpha) + (triangle->B.color * beta) + (triangle->C.color * gamma)};
    }
};


#endif //ASSIGNMENT_3_TRIANGLE_H
