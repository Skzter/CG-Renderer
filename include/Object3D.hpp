#pragma once

#include "Vector3D.hpp"
#include "Face3D.hpp"
#include <vector>
class Object3D
{
    std::vector<Vector3D> points;
    std::vector<Face3D> faces;
};
