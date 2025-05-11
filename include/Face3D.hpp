#pragma once

#include "Vector3D.hpp"
#include <ostream>
#include <vector>

class Face3D{
    std::vector<Vector3D*> points;
    Vector3D normal;

    public:
        Face3D();
        Face3D(std::vector<Vector3D*>);
        const std::vector<Vector3D*>* getPoints(){
            return &(this->points);
        }
};

std::ostream* operator<<(Face3D face, std::ostream out){
    out << "Face: " << std::endl;
    for(Vector3D* vec : *face.getPoints()){
        out << *vec << std::endl;
    }
}