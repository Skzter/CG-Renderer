#include "../include/Texture.hpp"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

Texture::Texture(char* filename)
{
    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
    if (data) {
        std::cout << "Loaded texture: " << width << "x" << height << ", channels: " << channels << std::endl;
        // Use image data here (data is a pointer to the pixel data)
        this->textureData = data;
    } else {
        std::cerr << "Failed to load image: " << stbi_failure_reason() << std::endl;
    }
    this->width = width;
    this->height = height;
    this->channels = channels;
}

Texture::~Texture(){
    stbi_image_free(this->textureData);
}

Color Texture::get(size_t x, size_t y){
    //std::cout << x << " " << y << std::endl;

    if(x >= width || y >= height){
        throw std::runtime_error("out of bound access on texture");
    }

    size_t pos = y * width + x;
    uint8_t r = textureData[channels * pos];
    uint8_t g = textureData[channels * pos + 1];
    uint8_t b = textureData[channels * pos + 2];
    return Color(r,b,g);
}