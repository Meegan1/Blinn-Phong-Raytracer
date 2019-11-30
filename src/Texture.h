//
// Created by Jake Meegan on 17/11/2019.
//

#include <fstream>
#include "Image.h"

#ifndef ASSIGNMENT_3_TEXTURE_H
#define ASSIGNMENT_3_TEXTURE_H

#endif //ASSIGNMENT_3_TEXTURE_H

/*
 * Loads texture into Image
 */
struct Texture {
    Image texture;

    // Load texture from file
    explicit Texture(const char* fileName);

    // Subscript overload to allow for texture to be access [x][y]
    std::vector<RGB> & operator[] (int x);

    // Arrow operator overload to allow Image methods to be accessed
    Image * operator -> ();
};