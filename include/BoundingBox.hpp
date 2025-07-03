#pragma once
#include "Vector3D.hpp"

class BoundingBox{
    public:
    Vector3D p1;
    Vector3D p2;

    bool contains(Vector3D&);
    void expandToInclude(BoundingBox);
};



