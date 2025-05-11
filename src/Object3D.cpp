#include "../include/Object3D.hpp"
#include <vector>

Object3D::Object3D(){};

Object3D::Object3D(std::vector<Vector3D>& points, std::vector<Face3D>& faces){
    this->points = points;
    this->faces = faces; 
}