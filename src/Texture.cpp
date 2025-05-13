#include "../include/Texture.hpp"

Texture::Texture(Color color, float opacity = 1)
{
    this->color = color;
    this->opacity = opacity;
}

Texture::Texture(){}