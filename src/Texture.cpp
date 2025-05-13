#include "../include/Texture.hpp"

Texture::Texture(Color color, uint8_t opacity = 255)
{
    this->color = color;
    this->opacity = opacity;
}

Texture::Texture(){}

std::ostream& operator<<(std::ostream& out, Texture texture){
    return out << "[" << texture.color << "|" << (int)texture.opacity << "]"; 
}