//
// Created by Jake Meegan on 02/12/2019.
//

#ifndef ASSIGNMENT_4_LIGHT_H
#define ASSIGNMENT_4_LIGHT_H

#include <random>
#include "Vector.h"
#define SAMPLE_COUNT 10

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


    /*
     * Compute ambient lighting for light -> surface
     */
    RGB computeAmbient(Triangle &surface, RGB &color) {
        return color * (this->ambient * surface.ambient);
    }

    /*
     * Compute diffuse lighting for light -> surface
     */
    RGB computeDiffuse(Triangle &surface, Vector &normal, RGB &surface_color, Vector &point) {
        float diffuse_angle = std::fmax(normal.dot((point - this->position).normalize()), 0.0f);
        float distance = (this->position - point).magnitude();
        float inverse_square = 1 / (distance * distance);

        return (color * surface_color * (surface.diffuse * diffuse_angle)) * inverse_square;
    }

    /*
     * Compute specular lighting for light -> surface
     */
    RGB computeSpecular(Triangle &surface, Vector &normal, Vector &point, Vector &ray_direction) {
        Vector halfDirection = (((point - this->position).normalize() + ray_direction) / 2).normalize();
        float specular_angle = halfDirection.dot(normal);
        float distance = (this->position - point).magnitude();

        return color * surface.specular * pow(specular_angle, surface.specular_coefficient);
    }
};

class AreaLight : public Light {
public:
    Vector v0, v1, v2, normal;
    float area, intensity;

    AreaLight(Vector color, Vector v0, Vector v1, Vector v2, float intensity) : Light(
            0,
            0,
            color,
            1),
            v0(v0), v1(v1), v2(v2),
            intensity(intensity)
            {
        Vector n = (v1 - v0).cross(v2 - v0);
        normal = n.normalize();
        area = 0.5f * n.magnitude();
    }

    Vector sample() {
        float u, v;
        static std::default_random_engine generator;
        static std::uniform_real_distribution<float> distribution{0,1.0f};
        do {
            u = distribution(generator);
            v = distribution(generator);
        }
        while (u+v >= 1);
        return v0 * (1 - u - v) + (v1*u) + (v2*v);
    }

    std::vector<Vector> samplePoints() {
        std::vector<Vector> points;
        for(int i = 0; i <= SAMPLE_COUNT; i++) {
            points.emplace_back(sample());
        }
        return points;
    }
};

#endif //ASSIGNMENT_4_LIGHT_H
