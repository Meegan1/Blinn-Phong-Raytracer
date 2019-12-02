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

    Camera camera(Vector(0, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0), 128, 128, 90);

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

    Camera camera(Vector(0, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0), 128, 128, 90);

    RGB A_COLOR = triangle.A.color/triangle.A.position.z;
    RGB B_COLOR = triangle.B.color/triangle.B.position.z;
    RGB C_COLOR = triangle.C.color/triangle.C.position.z;

    float A_DEPTH(1/triangle.A.position.z);
    float B_DEPTH(1/triangle.B.position.z);
    float C_DEPTH(1/triangle.C.position.z);

    for(int y = image.get_height()-1; y != -1; y--) {
        for (int x = 0; x < image.get_width(); x++) {
            Ray r = camera.pixelToRay(Pixel(x, y));
            float alpha, beta, gamma;
            if(r.intersects(triangle, alpha, beta, gamma)) {
                float r = clamp((alpha * A_COLOR.r) + (beta * B_COLOR.r)
                                      + (gamma * C_COLOR.r));
                float g = clamp((alpha * A_COLOR.g) + (beta * B_COLOR.g)
                                      + (gamma * C_COLOR.g));
                float b = clamp((alpha * A_COLOR.b) + beta * (B_COLOR.b)
                                      + (gamma * C_COLOR.b));

                float z = 1 / (alpha * A_DEPTH + beta * B_DEPTH + gamma * C_DEPTH);
                r *= z;
                g *= z;
                b *= z;
                image[x][y].r = (Color) r;
                image[x][y].g = (Color) g;
                image[x][y].b = (Color) b;
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