#pragma once
#include "Vector3D.hpp"
#include <vector>
#include "Face3D.hpp"

struct BoundingBox{
    Vector3D p1;
    Vector3D p2;
};

struct ArrBoundingBox : public BoundingBox{
    std::vector<Face3D*> faces;
    bool stop = false;
};
