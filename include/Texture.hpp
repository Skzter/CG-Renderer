#include "Color.hpp"
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <stdexcept>

class Texture
{
    unsigned char* textureData;
    uint8_t channels;
    size_t width, height;
public:
    Texture();
    Texture(std::string filename);
    size_t getWidth(){
        return this->width;
    }
    size_t getHeight(){
        return this->height;
    }

    Color get(size_t x, size_t y);
    void free();
};
