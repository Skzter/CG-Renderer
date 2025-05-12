#include "../include/Object3D.hpp"
#include <vector>
#include <iostream>

Object3D::Object3D(){};

Object3D::Object3D(std::vector<Vector3D> points, std::vector<std::vector<int>> faces){
    
    this->points = points;
    this->faces.reserve(faces.size());
    for(std::vector<int> face : faces){
        std::vector<Vector3D*> faceverts;
        faceverts.reserve(face.size());
        for(int vert : face){
            faceverts.push_back(&this->points.at(vert));
        }
        this->faces.push_back(Face3D(faceverts, Texture(Color(255,100,100), 1)));
    }
}


std::ostream& operator<<(std::ostream& out, Object3D obj){
    out << "Points: " << std::endl;
    for(Vector3D point : obj.getPoints()){
        out << point << std::endl;
    }
    
    out << "Faces: " << std::endl;
    for(Face3D face : obj.getFaces()){
        out << face;
    }

    return out;
}