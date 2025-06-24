#pragma once

#include "Hitpoint.hpp"
#include "Ray.hpp"
class IBinaryDisect{
    public:
        virtual Hitpoint closestHitpoint(Ray&) = 0;
        virtual void dealoc() = 0;
};

