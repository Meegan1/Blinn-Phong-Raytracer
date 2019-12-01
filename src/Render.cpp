//
// Created by Jake Meegan on 17/11/2019.
//

#include "Render.h"
#include "Triangle.h"
#include "Camera.h"


void Render::intersection() {
    Image image(128);
    Triangle triangle(
            Vertex(Vector(61, 10, 1), RGB(255, 0, 0), UV(0.160268, 0.290086)),
            Vertex(Vector(100, 100, 1), RGB(0, 255, 0), UV(0.083611, 0.159907)),
            Vertex(Vector(25, 90, 1), RGB(0, 0, 255), UV(0.230169, 0.222781))
    ); // create triangle with attributes

    Camera camera(Vector(0, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0), 90);

    for(int y = image.get_height()-1; y != -1; y--) {
        for (int x = 0; x < image.get_width(); x++) {
            Ray r = camera.pixelToRay(Pixel(x, y));
            if(r.intersects(triangle)) {
                image[x][y].r = 0;
                image[x][y].g = 0;
                image[x][y].b = 0;
            }
        }
    }
    image.toFile("intersection");
}

void Render::barycentric() {
    Image image(128);
    Triangle triangle(
            Vertex(Vector(61, 10, 1), RGB(255, 0, 0), UV(0.160268, 0.290086)),
            Vertex(Vector(100, 100, 1), RGB(0, 255, 0), UV(0.083611, 0.159907)),
            Vertex(Vector(25, 90, 1), RGB(0, 0, 255), UV(0.230169, 0.222781))
    ); // create triangle with attributes

    Camera camera(Vector(0, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0), 90);

    for(int y = image.get_height()-1; y != -1; y--) {
        for (int x = 0; x < image.get_width(); x++) {
            Ray r = camera.pixelToRay(Pixel(x, y));
            float alpha, beta, gamma;
            if(r.intersects(triangle, alpha, beta, gamma)) {
                Color color_r = clamp((alpha * triangle.A.color.r) + (beta * triangle.B.color.r)
                                      + (gamma * triangle.C.color.r));
                Color color_g = clamp((alpha * triangle.A.color.g) + (beta * triangle.B.color.g)
                                      + (gamma * triangle.C.color.g));
                Color color_b = clamp((alpha * triangle.A.color.b) + beta * (triangle.B.color.b)
                                      + (gamma * triangle.C.color.b));
                image[x][y].r = color_r;
                image[x][y].g = color_g;
                image[x][y].b = color_b;
            }
        }
    }
    image.toFile("barycentric");
}

/*
 * Sets min/max values of value to 0-255
 */
int Render::clamp(int value) {
    if (value > 255)
        return 255;
    else if (value < 0)
        return 0;
    else
        return value;
}