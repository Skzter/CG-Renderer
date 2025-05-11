#pragma once
#include "Vector3D.hpp"
#include "Face3D.hpp"
#include <ostream>
#include <vector>

class Object3D
{
    std::vector<Vector3D> points;
    std::vector<Face3D> faces;

    public:
        Object3D();
        Object3D(std::vector<Vector3D>&, std::vector<Face3D>&);


        const std::vector<Vector3D>& getPoints(){
            return (this->points);
        }

        const std::vector<Face3D>& getFaces(){
            return (this->faces);
        }
};

std::ostream& operator<<(std::ostream& out, Object3D obj){
    out << "Points: " << std::endl;
    for(Vector3D point : obj.getPoints()){
        out << point << std::endl;
    }
    
    out << "Faces: " << std::endl;
    for(Face3D face : obj.getFaces()){
        out << face << std::endl;
    }

    return out;
}
