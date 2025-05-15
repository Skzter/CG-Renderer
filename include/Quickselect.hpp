#pragma once
#include <vector>
#include <iostream>
#include "Face3D.hpp"
#include "limits"

namespace Quickselect{
    int partitionDir(std::vector<Face3D*> arr, int l, int r, size_t dir);
    Vector3D kthSmallestDir(std::vector<Face3D*>& arr, int l, int r, int k, size_t dir);
}
