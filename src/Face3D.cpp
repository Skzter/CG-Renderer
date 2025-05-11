#include "../include/Face3D.hpp"
#include <vector>

Face3D::Face3D(std::vector<Vector3D*> points){
    this->points = points;
    this->normal = Vector3D(0,0,0);
}