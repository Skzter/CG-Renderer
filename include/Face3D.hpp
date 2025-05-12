#pragma once
#include "Vector3D.hpp"
#include <ostream>
#include <vector>
#include "Color.hpp"
#include "Texture.hpp"

class Face3D{
public:
    std::vector<Vector3D*> points;
    Vector3D normal;
    Texture texture;

    Face3D();
    Face3D(std::vector<Vector3D*>, Texture);
};

std::ostream& operator<<(std::ostream& out, Face3D face);