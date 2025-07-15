#include "../include/Texture.hpp"
#include <cstddef>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

Texture::Texture(){
    this->textureData = NULL;
}

Texture::Texture(std::string filename)
{
    int width, height, channels;
    std::cout << filename.data() << std::endl;
    unsigned char* data = stbi_load(filename.data(), &width, &height, &channels, 0);
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

void Texture::free(){
    stbi_image_free(this->textureData);
}

Color Texture::get(size_t x, size_t y){
    if(this->textureData == NULL){
        return Color();
    }
    //std::cout << x << " " << y << std::endl;

    if(x >= width || y >= height){
        throw std::runtime_error("out of bound access on texture");
    }

    size_t pos = y * width + x;
    uint8_t r = textureData[channels * pos + 0];
    uint8_t g = textureData[channels * pos + 1];
    uint8_t b = textureData[channels * pos + 2];
    return Color(r,g,b);
}
