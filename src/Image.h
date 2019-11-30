//
// Created by Jake Meegan on 16/11/2019.
//

#include <vector>
#include <fstream>
#include <iostream>
#include "Vertex.h"

#ifndef ASSIGNMENT_3_IMAGE_H
#define ASSIGNMENT_3_IMAGE_H

#endif //ASSIGNMENT_3_IMAGE_H

/*
 * Class for storing pixels/colours in an image
 */
class Image {
public:
    // Default constructor to initialise width/height to 0
    Image() : width(0), height(0) {}

    // Constructor for 1:1 size
    explicit Image(unsigned int size);

    // Constructor for custom aspect ratio
    explicit Image(unsigned int width, unsigned int height);

    // Prints image to .ppm format
    void toFile(const std::string& f_name);

    // Getter for width
    unsigned long get_width();

    // Getter for height
    unsigned long get_height();

    // Overload Subscript operator to allow for access to pixels
    std::vector<RGB> & operator[] (int x);

private:
    std::vector<std::vector<RGB>> image;
    unsigned long width, height;
};