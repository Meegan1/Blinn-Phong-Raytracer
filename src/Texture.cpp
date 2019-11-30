//
// Created by Jake Meegan on 17/11/2019.
//

#include "Texture.h"

Texture::Texture(const char *fileName) {
    // open the input file
    std::ifstream inFile(fileName);
    if (inFile.bad())
        return;

    // get length of file
    inFile.seekg (0, inFile.end);
    long length = inFile.tellg();
    inFile.seekg (0, inFile.beg);

    std::string string;
    inFile >> string;
    if(string != "P3") // file not valid ppm
        return;

    inFile.ignore(length, '\n'); // skip line
    inFile.ignore(length, '\n'); // skip comment

    int width, height;
    inFile >> width >> height; // get dimensions

    inFile.ignore(length, '\n'); // skip line
    inFile.ignore(length, '\n'); // skip max value

    texture = Image(width, height); // create object to store texture

    // read through file to get colors
    for(int y = height - 1; y != -1; y--) {
        for(int x = 0; x < width; x++) {
            int r, g, b;
            inFile >> r >> g >> b;

            texture[x][y].r = r;
            texture[x][y].g = g;
            texture[x][y].b = b;
        }
    }
    inFile.close(); // close file
}

std::vector<RGB> &Texture::operator[](int x) {
    return texture[x];
}

Image *Texture::operator->() {
    return &texture;
}
