#pragma once
#include "BoundingBox.hpp"
#include "IBinaryDisect.hpp"
#include "vector"

class BinaryArray : IBinaryDisect{
    public:
        std::vector<float> boxes;
        std::vector<std::vector<Face3D*>> allfaces;
        
        BinaryArray(std::vector<Face3D*> faces, int maxDepth, BoundingBox box);

        Hitpoint closestHitpoint(Ray&);
        void dealoc();

        void buildArray(size_t pos, u_int8_t dir, BoundingBox box, std::vector<Face3D*> faces);
};