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
    Vector3D middlePoint();

    float maxW(size_t dir);
    float minW(size_t dir);

    static bool smallerEqDir(Face3D*, Face3D*, size_t);
};

std::ostream& operator<<(std::ostream& out, Face3D face);

std::pair<std::vector<Face3D*>, std::vector<Face3D*>> disect(std::vector<Face3D*> faces, uint8_t dir, float value);

