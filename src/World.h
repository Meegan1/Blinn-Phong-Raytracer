//
// Created by Jake Meegan on 19/12/2019.
//

#ifndef ASSIGNMENT_4_WORLD_H
#define ASSIGNMENT_4_WORLD_H


#include <vector>
#include <random>
#include "Light.h"
#include "Ray.h"

class World {
public:
    std::vector<Triangle> triangles;
    std::vector<Light> pointLights;
    std::vector<Light> areaLights;

    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution{-1.0f,1.0f};

    void addTriangle(const Triangle &triangle) {
        triangles.emplace_back(triangle);
    }

    void addPlane(const Vector &v0, const Vector &v1, const Vector &v2, const Vector &v3, const RGB &color,
                  const Vector &ambient,
                  const Vector &diffuse, const Vector &specular, float specular_coefficient) {
        triangles.emplace_back(
                Vertex(v0, color, UV(0, 0)),
                Vertex(v1, color, UV(0, 0)),
                Vertex(v3, color, UV(0, 0)),
                ambient,
                diffuse,
                specular,
                specular_coefficient
        );

        triangles.emplace_back(
                Vertex(v1, color, UV(0, 0)),
                Vertex(v2, color, UV(0, 0)),
                Vertex(v3, color, UV(0, 0)),
                ambient,
                diffuse,
                specular,
                specular_coefficient
        );
    }

    void addPointLight(const Light &light) {
        pointLights.emplace_back(light);
    }

    void addAreaLight(const Light &light) {
        areaLights.emplace_back(light);
    }

    Surfel intersects(Ray &ray, float &dist) {
        float z_buffer = MAXFLOAT;
        Triangle *triangle = nullptr;
        Vector point;
        float alpha = 0, beta = 0, gamma = 0;
        for (Triangle &surface : triangles) {
            float distance = 0;
            Vector p;
            float a = 0, b = 0, g = 0;
            if (ray.intersects(surface, p, distance, a, b, g)) {
                if (distance >= z_buffer)
                    continue;
                z_buffer = distance;
                triangle = &surface;
                point = p;
                alpha = a;
                beta = b;
                gamma = g;
            }
        }
        return {triangle, point, alpha, beta, gamma};
    }

    bool lineOfSight(Vector &point_a, Vector &point_b) {
        Vector direction =  point_a - point_b;
        Ray ray(point_b, direction);
        float z_buffer = direction.magnitude();

        for (Triangle &surface : triangles) {
            float distance;
            if(ray.intersects(surface, distance)) {
                if(distance > z_buffer)
                    continue;
                z_buffer = distance;
            }
        }

        return (z_buffer >= direction.magnitude() - 0.00001);
    }

    Vector estimateDirectPointLight(Surfel &surfel, Ray &ray) {
        Vector output(0);

        for(Light &light : pointLights) {
            if(lineOfSight(surfel.location, light.position)) { // not in shadow
                Vector omega_i = surfel.location - light.position;
                float distance = omega_i.magnitude();
                Vector E_I = light.color / (4 * M_PI * distance * distance);

                output+= surfel.BSDF(omega_i, -ray.direction) * E_I * std::max(0.0f, omega_i.dot(surfel.normal));
            }
        }

        return output;
    }


    Vector estimateDirectAreaLight(Surfel &surfel, Ray &ray) { // todo finish arealight
        Vector output(0);

        for(Light &light : areaLights) {
            if(lineOfSight(light.position, surfel.location)) { // not in shadow
                Vector color = surfel.color();
                output += light.computeDiffuse(*surfel.triangle, surfel.normal, color, surfel.location);
            }
        }

        return output;
    }

    Vector estimateImpulseScattering(Surfel &surfel, Ray &ray, int depth) {
        Vector vec = -ray.direction;
        Vector impulseDirection = surfel.getImpulseDirection(vec);
        Ray secondaryRay(surfel.location, impulseDirection);

        depth++;
        if(depth <= 4) {
            Vector temp = pathTrace(secondaryRay, false, depth, true);
            return temp * surfel.impulse.magnitude();
        }
        else
            return {0};
    }

    Vector estimateIndirectLight(Surfel &surfel, Ray &ray, int depth) {
        int ran = random() % 100;
        if(ran > surfel.extinction_probability()-1)
            return 0;
        else {
            float x = distribution(generator);
            float y = distribution(generator);
            float z = distribution(generator);
            Vector r(x, y, z);

            if(r.normalize().dot(surfel.normal) >= 0)
                r = -r;

            Ray bounceRay(surfel.location, r);
            return pathTrace(bounceRay, false, depth);
        }
    }

    Vector pathTrace(Ray &ray, bool is_eye_ray,  int depth, bool reflect = false) {
        Vector output(0);
        float distance = 0;

        Surfel surfel = intersects(ray, distance);
        if(surfel.triangle) {
            if(is_eye_ray && surfel.emits)
                output += surfel.triangle->emission;

            output += estimateDirectPointLight(surfel, ray);
            output += estimateDirectAreaLight(surfel, ray);


            if(!is_eye_ray && surfel.impulse.magnitude() > 0) // get reflection
                output += estimateImpulseScattering(surfel, ray, depth);


            if(is_eye_ray) {
                int N = 16; // number of random directions
                Vector indirectLightingApprox = 0;
                for (int n = 0; n < N; ++n) {
                    // cast a ray above P in random direction in hemisphere oriented around N, the surface normal at P
                    indirectLightingApprox += estimateIndirectLight(surfel, ray, depth); // accumulate results
                }
                // divide by total number of directions taken
                output += indirectLightingApprox / N;
            }
        }
        depth++;
        return output;
    }
};


#endif //ASSIGNMENT_4_WORLD_H
