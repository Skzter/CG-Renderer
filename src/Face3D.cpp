#include "../include/Face3D.hpp"
#include <vector>

Face3D::Face3D(std::vector<Vector3D*> points, Texture texture){
    this->points = points;
    Vector3D vec1 = *points.at(1) - *points.at(0);
    Vector3D vec2 = *points.at(2) - *points.at(0);
    this->normal = Vector3D::cross(vec1,vec2);
    this->texture = texture;
}

Face3D::Face3D(){};

std::ostream& operator<<(std::ostream& out, Face3D face){
    out << "Face : " << std::endl << "Normal : " << face.normal << std::endl;
    for(Vector3D* vec : face.points){
        out << *vec << std::endl;
    }
    return out;
}