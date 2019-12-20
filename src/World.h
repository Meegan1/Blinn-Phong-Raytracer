//
// Created by Jake Meegan on 19/12/2019.
//

#ifndef ASSIGNMENT_4_WORLD_H
#define ASSIGNMENT_4_WORLD_H


#include <vector>
#include "Light.h"
#include "Ray.h"

class World {
public:
    std::vector<Triangle> triangles;
    std::vector<Light> pointLights;
    std::vector<Light> areaLights;


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
                Vector E_I = light.colour / (4 * M_PI * distance * distance);

                output+= surfel.BSDF(omega_i, -ray.direction) * E_I * std::max(0.0f, omega_i.dot(surfel.normal));
            }
        }

        return output;
    }


    Vector estimateDirectAreaLight(Surfel &surfel, Ray &ray) { // todo finish arealight
        Vector output(0);

        for(Light &light : areaLights) {
            if(lineOfSight(light.position, surfel.location)) { // not in shadow
                Vector omega_i = light.position - surfel.location;
                float distance = omega_i.magnitude();

                Vector E_I = light.colour / (4 * M_PI * distance * distance);

                output += surfel.BSDF(omega_i, -ray.direction) * E_I * std::max(0.0f, omega_i.dot(surfel.normal));
            }
        }

        return output;
    }

    Vector estimateImpulseScattering(Surfel &surfel, Ray &ray, bool is_eye_ray) {
        Vector impulseDirection = surfel.getImpulseDirection(-ray.direction);
        Ray secondaryRay(surfel.location, impulseDirection);

        return pathTrace(secondaryRay, is_eye_ray);
    }

    Vector estimateIndirectLight(Surfel &surfel, Ray &ray, bool is_eye_ray) {
        if(random() > surfel.extinction_probability())
            return 0;
        else {
            Vector bounceVector = surfel.normal;
            Ray bounceRay(surfel.location, bounceVector);
            return pathTrace(bounceRay, false);
        }
    }

    Vector pathTrace(Ray &ray, bool is_eye_ray) {
        Vector output(0);
        float distance = 0;

        Surfel surfel = intersects(ray, distance);
        if(surfel.triangle) {
            if(is_eye_ray && surfel.emits)
                output += surfel.triangle->emission;

            if(!is_eye_ray || surfel.reflects_direct) {
                output += estimateDirectPointLight(surfel, ray);
                output += estimateDirectAreaLight(surfel, ray);
            } // direct illumination

            if(!is_eye_ray || surfel.scatterImpulse)
                output += estimateImpulseScattering(surfel, ray, is_eye_ray);

            bool m_indirect = false;
            if(!is_eye_ray || m_indirect) {
                output += estimateIndirectLight(surfel, ray, is_eye_ray);
            }
        }
        return output;
    }
};


#endif //ASSIGNMENT_4_WORLD_H
