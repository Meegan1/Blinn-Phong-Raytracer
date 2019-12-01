//
// Created by Jake Meegan on 28/11/2019.
//

#include <cmath>
#include "Ray.h"

#ifndef ASSIGNMENT_3_CAMERA_H
#define ASSIGNMENT_3_CAMERA_H

#endif //ASSIGNMENT_3_CAMERA_H

struct Pixel {
    float x, y;
    Pixel(float x, float y) : x(x), y(y) {}
};

struct Camera {
    Vector position;
    Vector direction;
    Vector up;
    float fov;
    float angle;

    Camera(Vector position, Vector direction, Vector up, float FOV) : position(position), direction(direction), up(up), fov(FOV), angle(0) {
        angle = tan(FOV * 0.5f * ((float)M_PI / 180));
    }

    Ray pixelToRay(Pixel pixel) {
        float nx = (((2*(pixel.x + 0.5f)/128)-1) * angle)*128;
        float ny = (((2*(pixel.y + 0.5f)/128)-1) * angle)*128;
        return {Vector(position.x, position.y, position.z), Vector(nx, ny, 1).normalize()};
    }
};