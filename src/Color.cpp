#include "../include/Color.hpp"

Color::Color(){
    this->r = 0;
    this->b = 0;
    this->g = 0;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b){
            this->r = r;
            this->b = b;
            this->g = g;
}

std::ostream& operator<<(std::ostream& out, Color c){
    return out << "[" << (int)c.getr() << "|" << (int)c.getg() << "|" << (int)c.getb() << "]"; 
}

Color Color::operator*(const float a) const
{
    float r = this->r * a;
    float g = this->g * a;
    float b = this->b * a;
    return Color(r,g,b);
}
