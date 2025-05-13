#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"
#include "../include/Color.hpp"
#include <cstdint>
#include <iostream>


int main()
{
    const int width = 2;
    const int height = 2;
    Color pixels[width * height] = {
        Color(0, 0, 0),  // Red
        Color(255, 255, 255),  // Green
        Color(0, 0, 0),  // Blue
        Color(255, 255, 255) // Yellow
    };

    // Create a buffer for RGB data
    uint8_t *buffer = new uint8_t[width * height * 3];
    for (int i = 0; i < width * height; ++i)
    {
        buffer[i * 3] = pixels[i].getr();     // Red
        buffer[i * 3 + 1] = pixels[i].getg(); // Green
        buffer[i * 3 + 2] = pixels[i].getb(); // Blue
    }

    // Write to PNG (3 = RGB channels)
    int success = stbi_write_png("output.png", width, height, 3, buffer, width * 3);
    delete[] buffer;

    if (!success)
    {
        std::cerr << "Failed to write PNG!" << std::endl;
        return 1;
    }

    return 0;
}