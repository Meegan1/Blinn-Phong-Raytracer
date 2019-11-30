//
// Created by Jake Meegan on 16/11/2019.
//

#include "Image.h"


Image::Image(unsigned int size) : image(size), width(size), height(size) {
    for(auto & row : image) {
        row.resize(size, RGB(255, 255, 192)); // intitialise each pixel to default colour
    }
}

Image::Image(unsigned int width, unsigned int height) : image(width), width(width), height(height) {
    for(auto & row : image) {
        row.resize(height, RGB(255, 255, 192)); // intitialise each pixel to default colour
    }
}

void Image::toFile(const std::string &f_name) {
    std::ofstream outFile(f_name + ".ppm", std::ofstream::out);
    unsigned long size = image.size();

    // output header to file
    outFile << "P3" << std::endl;
    outFile << "# " << f_name << std::endl;
    outFile << width << " " << height << std::endl;
    outFile << "255" << std::endl;

    // output pixels to file
    for (unsigned long y = height-1; y != -1; y--) {
        for (unsigned long x = 0; x < width; x++) {
            outFile << (int) image[x][y].r << " " << (int) image[x][y].g << " " << (int) image[x][y].b << " ";

        }
        outFile << std::endl;
    }

    outFile.close(); //  close file

    std::cout << f_name << " has been generated" << std::endl;
}

unsigned long Image::get_width() {
    return width;
}

unsigned long Image::get_height() {
    return height;
}

std::vector<RGB> &Image::operator[](int x) {
    return image[x];
}
