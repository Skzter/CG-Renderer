#include "../include/Object3D.hpp"
#include <vector>
#include <iostream>
#include <limits>

Object3D::Object3D(){};

Object3D::Object3D(std::vector<Vector3D> points, std::vector<std::vector<int>> faces, int depth){
    
    this->points = points;
    this->faces.reserve(faces.size());

    for(std::vector<int> face : faces){
        std::vector<Vector3D*> faceverts;
        faceverts.reserve(face.size());
        for(int vert : face){
            faceverts.push_back(&this->points.at(vert));
        }
        this->faces.push_back(Face3D(faceverts, Texture(Color(255,100,100), 
        1)));
    }

    Vector3D biggest;
    Vector3D smallest;
    for(size_t i = 0; i < 3; i++){
        biggest.at(i) = std::numeric_limits<float>::min();
        smallest.at(i) = std::numeric_limits<float>::max();
    }
    for(Vector3D v : points){
        for(size_t i = 0; i < 3; i++){
            if(v.at(i) > biggest.at(i)){
                biggest.at(i) = v.at(i);
            }
            if(v.at(i) < smallest.at(i)){
                smallest.at(i) = v.at(i);
            }
        }
    }
    BoundingBox box;
    box.p1 = smallest;
    box.p2 = biggest;

    std::vector<Face3D*> treeFaces;
    treeFaces.reserve(this->faces.size());
    for(size_t i = 0; i < this->faces.size(); i++){
        treeFaces.push_back(&this->faces.at(i));
    }
    this->disect = BinaryLinkedTree::createNode(treeFaces, depth, box);
}

Object3D::~Object3D(){
    this->disect->dealoc();
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