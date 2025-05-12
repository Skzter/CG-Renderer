#include "../include/Face3D.hpp"
#include <vector>

Face3D::Face3D(std::vector<Vector3D*> points){
    this->points = points;
    this->normal = Vector3D(0,0,0);
}

Face3D::Face3D(){};

std::ostream& operator<<(std::ostream& out, Face3D face){
    out << "Face (Color : " << face.getColor() << "): " << std::endl;
    for(Vector3D* vec : face.getPoints()){
        out << *vec << std::endl;
    }
    return out;
}