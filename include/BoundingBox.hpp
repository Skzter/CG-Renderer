#pragma once
#include "Vector3D.hpp"

struct BoundingBox{
    Vector3D p1;
    Vector3D p2;
};

bool contains(BoundingBox, Vector3D);



