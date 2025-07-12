#include "Color.hpp"
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <stdexcept>

class Texture
{
    unsigned char* textureData;
    size_t width, height;
    uint8_t channels;
public:
    Texture();
    Texture(std::string filename);
    ~Texture();
    size_t getWidth(){
        return this->width;
    }
    size_t getHeight(){
        return this->height;
    }

    Color get(size_t x, size_t y);
};
