#pragma once
#include "Vector3D.hpp"
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <vector>
#include "Color.hpp"
#include "Texture.hpp"
#include <algorithm>
#include "BoundingBox.hpp"

class Face3D{
public:
    std::vector<Vector3D*> points;
    Vector3D normal;

    Face3D();
    Face3D(std::vector<Vector3D*>);
    Vector3D middlePoint();

    float maxW(size_t dir);
    float minW(size_t dir);

    static bool smallerEqDir(Face3D*, Face3D*, size_t);
};

std::ostream& operator<<(std::ostream& out, Face3D face);

std::pair<std::vector<Face3D*>, std::vector<Face3D*>> calcDisect(std::vector<Face3D*> faces, uint8_t dir, float value);
float calcDisectValue(uint8_t axis, std::vector<Face3D*> faces);
float calcOctDisectValue(BoundingBox box, uint8_t dir);

