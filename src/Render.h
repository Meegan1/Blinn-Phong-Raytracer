//
// Created by Jake Meegan on 17/11/2019.
//

#ifndef ASSIGNMENT_3_RENDER_H
#define ASSIGNMENT_3_RENDER_H

#include "Texture.h"

class Render {
public:
    // Clamp value between 0-255
    static int clamp(int value);

    static RGB BilinearLookup(Texture& tex, float s, float t);

    static void abg();

    static void half_plane();

    static void triangle();

    static void rgb();

    static void texture();

    static void ray();
};


#endif //ASSIGNMENT_3_RENDER_H
