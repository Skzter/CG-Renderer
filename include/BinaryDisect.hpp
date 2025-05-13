#pragma once
#include "Face3D.hpp"

struct BoundingBox{
    Vector3D p1;
    Vector3D p2;
};

class BinaryDisect{
    public:
        BinaryDisect* left;
        BinaryDisect* right;
        std::vector<Face3D*> faces;

        BinaryDisect(std::vector<Face3D*> faces, int maxDepth, BoundingBox box);

        static std::vector<BinaryDisect> all;
};