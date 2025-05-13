#include "Color.hpp"

class Texture
{
public:
    Color color = Color(0,0,0);
    float opacity = 1;

    Texture();
    Texture(Color color, float opacity);
};