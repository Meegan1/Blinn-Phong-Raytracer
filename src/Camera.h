//
// Created by Jake Meegan on 28/11/2019.
//

#include <cmath>

#ifndef ASSIGNMENT_3_CAMERA_H
#define ASSIGNMENT_3_CAMERA_H
#include "Ray.h"

struct Pixel {
    float x, y;
    Pixel(float x, float y) : x(x), y(y) {}
};

struct Camera {
    Vector position;
    Vector forward;
    Vector up;
    Vector right = Vector(0, 0, 0);

    float fov, angle;
    float w, h;

    Camera(Vector position, Vector direction, Vector up, float w, float h, float FOV) : position(position),
                                                                                        forward(direction.normalize()),
                                                                                        up(up.normalize()), w(w), h(h),
                                                                                        fov(FOV) {
        angle = tan(FOV * 0.5f * ((float) M_PI / 180));

        right = forward.cross(up);
    }

    Ray pixelToRay(Pixel pixel) {
        Vector origin = position;

        // get perspective either side of camera
        float nx = (((2*(pixel.x + 0.5f)/w)-1) * angle);
        float ny = (((2*(pixel.y + 0.5f)/h)-1) * angle);

        // get direction from camera to world
        Vector dir = forward + (right * (nx)) + (up * (ny));

        return {origin, Vector(dir.x, dir.y, dir.z)};
    }
};

#endif //ASSIGNMENT_3_CAMERA_H
