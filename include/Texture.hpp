#include "Color.hpp"

class Texture
{
public:
    Color color = Color(0,0,0);
    uint8_t opacity = 255;

    Texture();
    Texture(Color color, uint8_t opacity);
};
    
std::ostream& operator<<(std::ostream& out, Texture Texture);