#include "../include/Color.hpp"

Color::Color(){
    this->r = 255;
    this->b = 255;
    this->g = 255;
    this->opacity = 1;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, float o = 1){
            this->r = r;
            this->b = b;
            this->g = g;
            this->opacity = o;
}

std::ostream& operator<<(std::ostream& out, Color c){
    return out << "[" << (int)c.getr() << "|" << (int)c.getg() << "|" << (int)c.getb() << "]"; 
}