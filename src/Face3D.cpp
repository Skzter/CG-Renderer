#include "../include/Face3D.hpp"
#include <vector>

Face3D::Face3D(std::vector<Vector3D*> points){
    this->points = points;
    Vector3D vec1 = *points.at(1) - *points.at(0);
    Vector3D vec2 = *points.at(2) - *points.at(1);
    this->normal = Vector3D::cross(vec1,vec2);
}

Face3D::Face3D(){};

std::ostream& operator<<(std::ostream& out, Face3D face){
    out << "Face (Color : " << face.getColor() << "): " << std::endl << "Normal : " << face.getNormal() << std::endl;
    for(Vector3D* vec : face.getPoints()){
        out << *vec << std::endl;
    }
    return out;
}