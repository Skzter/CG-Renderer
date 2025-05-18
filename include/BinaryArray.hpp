#pragma once
#include "BoundingBox.hpp"
#include "IBinaryDisect.hpp"
#include "vector"


class BinaryArray : public IBinaryDisect{
    public:
        uint8_t startdir;
        std::vector<ArrBoundingBox> disectValue;

        BinaryArray(ArrBoundingBox, std::vector<Face3D*>, size_t, uint8_t);
        Hitpoint closestHitpoint(Ray&);
        Hitpoint closestHitpointPos(Ray&, size_t);
        void dealoc();

        void initArray(size_t, ArrBoundingBox, std::vector<Face3D*>, uint8_t, size_t);
};