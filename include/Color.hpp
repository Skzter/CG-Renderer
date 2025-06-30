#pragma once
#include <cstdint>
#include <ostream>
#include <stdint.h>

class Color{
    uint8_t r;
    uint8_t g;
    uint8_t b;

    public:
        Color();
        Color(uint8_t, uint8_t, uint8_t);

        uint8_t getr(){
            return r;
        }
        uint8_t getg(){
            return g;
        }
        uint8_t getb(){
            return b;
        }
	Color operator*(const float a) const;
};

std::ostream& operator<<(std::ostream& out, Color c);
