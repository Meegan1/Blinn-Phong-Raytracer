//
// Created by Jake Meegan on 17/11/2019.
//

#include "Render.h"
#include "Triangle.h"
#include "Camera.h"


void Render::ray() {
    Image image(128);
    Triangle triangle(
            Vertex(Vector(61, 10, 1), RGB(255, 0, 0), UV(0.160268, 0.290086)),
            Vertex(Vector(100, 100, 1), RGB(0, 255, 0), UV(0.083611, 0.159907)),
            Vertex(Vector(25, 90, 1), RGB(0, 0, 255), UV(0.230169, 0.222781))
    ); // create triangle with attributes

    Camera camera(Vector(0, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0), 90);

    for(int y = 64; y < image.get_height(); y++) {
        for (int x = 100; x < image.get_width(); x++) {
            Ray r = camera.pixelToRay(Pixel(x, y));
            if(r.intersects(triangle)) {
                image[x][y].r = 0;
                image[x][y].g = 0;
                image[x][y].b = 0;
            }
        }
    }

    image.toFile("ray");
}

void Render::texture() {

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