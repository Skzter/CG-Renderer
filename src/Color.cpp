#include "../include/Color.hpp"
#include <sys/types.h>

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

void Color::operator+=(const Color& other)
{
    this->r = std::min((int)(this->r) + (int)(other.r), 255);
    this->g = std::min((int)(this->g) + (int)(other.g), 255);
    this->b = std::min((int)(this->b) + (int)(other.b), 255);
}

Color Color::on(const Color& other){
    uint8_t r = std::min(this->r, other.r);
    uint8_t g = std::min(this->g, other.g);
    uint8_t b = std::min(this->b, other.b);
    return Color(r,g,b);
}


