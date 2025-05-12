#pragma once
#include <cstdint>
#include <ostream>
#include <stdint.h>

class Color{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    float opacity;

    float surface; //irgendwelche Oberflächeninformationen

    public:
        Color();
        Color(uint8_t, uint8_t, uint8_t, float);

        uint8_t getr(){
            return r;
        }
        uint8_t getg(){
            return g;
        }
        uint8_t getb(){
            return b;
        }
        uint8_t geto(){
            return opacity;
        }
};

std::ostream& operator<<(std::ostream& out, Color c);