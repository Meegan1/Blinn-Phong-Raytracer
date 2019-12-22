//
// Created by Jake Meegan on 19/12/2019.
//

#ifndef ASSIGNMENT_4_WORLD_H
#define ASSIGNMENT_4_WORLD_H

#define PDF (1 / (2 * M_PI))

#include <vector>
#include <random>
#include "Light.h"
#include "Ray.h"

class World {
public:
    std::vector<Triangle> triangles;
    std::vector<Light> pointLights;
    std::vector<AreaLight> areaLights;

    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution{0,1.0f};
    std::uniform_real_distribution<float> extinction{0, 1.0f};

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

    void addAreaLight(const AreaLight &light) {
        areaLights.emplace_back(light);
    }

    bool intersects(Ray &ray, float &dist, Surfel &surfel) {// checks for intersection
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
        dist = z_buffer;

        Vector l_point;
        AreaLight *areaLight = nullptr;
        Vector l_color;
        Vector l_normal;
        for(AreaLight light : areaLights) {
            Triangle temp(
                    Vertex(light.v0, RGB(0), UV(0, 0)),
                    Vertex(light.v1, RGB(0), UV(0, 0)),
                    Vertex(light.v2, RGB(0), UV(0, 0))
            );
            float distance = 0;
            Vector p;
            float a = 0, b = 0, g = 0;
            if (ray.intersects(temp, p, distance, a, b, g)) {
                if (distance >= z_buffer)
                    continue;
                z_buffer = distance;
                l_point = p;
                areaLight = &light;
                l_color = light.color;
                l_normal = light.normal;
            }
        }

        if(dist >= z_buffer) {
            dist = z_buffer;
            if(areaLight != nullptr) {
                surfel = {l_point, l_color, l_normal};
                return true;
            }
        }

        if(triangle == nullptr)
            return false;

        surfel = {*triangle, point, alpha, beta, gamma};
        return true;
    }

    bool lineOfSight(Vector &point_a, Vector &point_b) { // check if point is occluded by another object
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
        Vector normal = surfel.normal.dot(ray.direction) < 0 ? surfel.normal : surfel.normal * -1; // get normal from side visible to ray

        for(Light &light : pointLights) {
            if(lineOfSight(surfel.location, light.position)) { // not in shadow
                Vector omega_i = light.position - surfel.location;
                float distance = omega_i.magnitude();
                Vector E_I = light.color / (4 * M_PI * distance * distance);

                output+= surfel.BSDF(omega_i, -ray.direction) * E_I * std::max(0.0f, omega_i.normalize().dot(normal));
            }
        }

        return output;
    }


    Vector estimateDirectAreaLight(Surfel &surfel, Ray &ray) {
        Vector output(0);
        Vector normal = surfel.normal.dot(ray.direction) < 0 ? surfel.normal : surfel.normal * -1; // get normal from side visible to ray

        for(AreaLight &light : areaLights) {
            Vector result;
            for(Vector &point : light.samplePoints()) {
                if (lineOfSight(point, surfel.location)) { // not in shadow
                    Vector omega_i = point - surfel.location;
                    float cosa = std::max(0.0f, omega_i.normalize().dot(normal));
                    float cosb = fmax((-omega_i.normalize()).dot(light.normal), 0.0f);
                    float distance = fmax(omega_i.magnitude(), 1.0f);
                    float E_I =  light.intensity / ( distance * distance);

                    result+= surfel.BSDF(omega_i, -ray.direction) * E_I * cosa * cosb;
                }
            }
            output += result * light.area * light.color / SAMPLE_COUNT;
        }

        return output;
    }

    Vector estimateImpulseScattering(Surfel &surfel, Ray &ray) {
        if(extinction(generator) <= surfel.extinction_probability())
            return 0;

        Vector impulseDirection = surfel.getImpulseDirection(ray.direction);
        Ray secondaryRay(surfel.location, impulseDirection);

        Vector temp = pathTrace(secondaryRay, false);
        return temp * surfel.impulse.magnitude(); // get reflection
    }

    Vector estimateIndirectLight(Surfel &surfel, Ray &ray) {
        if(extinction(generator) > surfel.extinction_probability())
            return 0;

        Vector indirectLightingApprox = 0;
        // create random vector for indirect lighting
        float r1 = distribution(generator);
        float r2 = distribution(generator);
        Vector sample = Vector::sampleHemisphere(r1, r2);

        Vector normal = surfel.normal.dot(ray.direction) < 0 ? surfel.normal : surfel.normal * -1; // get normal from side visible to ray

        Vector right, up;
        Vector::createCoordinateSystem(normal, right, up);

        Vector r(
                sample.x * right.x + sample.y * normal.x + sample.z * up.x,
                sample.x * right.y + sample.y * normal.y + sample.z * up.y,
                sample.x * right.z + sample.y * normal.z + sample.z * up.z
        );

        Ray bounceRay(surfel.location, r);

        indirectLightingApprox += pathTrace(bounceRay, false); // get indirect lighting
        return indirectLightingApprox;
    }

    Vector pathTrace(Ray &ray, bool is_eye_ray) {
        Vector output(0);
        float distance = 0;

        Surfel surfel;
        if(intersects(ray, distance, surfel)) { // intersects
            if (is_eye_ray && surfel.emits)
                output += surfel.emission; // add emission

            output += estimateDirectPointLight(surfel, ray); // get direct point lights
//            if(!is_eye_ray)
            output += estimateDirectAreaLight(surfel, ray); // get direct area light

            if (surfel.impulse.magnitude() > 0) // get reflection
                output += estimateImpulseScattering(surfel, ray);

            // get indirect lighting
            output += estimateIndirectLight(surfel, ray);
        }
        return output; // return final colour
    }
};


#endif //ASSIGNMENT_4_WORLD_H
