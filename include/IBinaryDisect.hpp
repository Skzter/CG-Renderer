#pragma once

#include "Hitpoint.hpp"
#include "Ray.hpp"
#include <cstddef>
#include <vector>
#include "Face3D.hpp"

class IBinaryDisect{
    public:
        virtual Hitpoint closestHitpoint(Ray&) = 0;
        virtual void dealoc() = 0;

        
    static int mostFaces;
    static int sumFaces;
    static int cntLeafs;

    static void incrCounters(size_t);
};

