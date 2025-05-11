#pragma once

#include "Vector3D.hpp"
#include <vector>

class Face3D{
    std::vector<Vector3D*> points;
    Vector3D normal;

    public:
        Face3D(std::vector<Vector3D*>);
};