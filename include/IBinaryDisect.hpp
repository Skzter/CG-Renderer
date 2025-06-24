#pragma once

#include "Hitpoint.hpp"
#include "Ray.hpp"
class IBinaryDisect{
    public:
        virtual Hitpoint closestHitpoint(Ray&) = 0;
        virtual void dealoc() = 0;

        
    static int mostFaces;
    static int sumFaces;
    static int cntLeafs;
};

