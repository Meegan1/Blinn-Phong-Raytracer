//
// Created by Jake Meegan on 19/12/2019.
//

#ifndef ASSIGNMENT_4_WORLD_H
#define ASSIGNMENT_4_WORLD_H


#include <vector>
#include "Triangle.h"
#include "Camera.h"
#include "Light.h"

class World {
public:
    std::vector<Triangle> triangles;
    std::vector<Light> lights;


    void addTriangle(const Triangle &triangle) {
        triangles.emplace_back(triangle);
    }

    void
    addPlane(const Vector &v0, const Vector &v1, const Vector &v2, const Vector &v3, const RGB &color,
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
    void addLight(const Light &light) {
        lights.emplace_back(light);
    }
};


#endif //ASSIGNMENT_4_WORLD_H
