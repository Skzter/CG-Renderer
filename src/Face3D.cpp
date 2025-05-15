#include "../include/Face3D.hpp"
#include <vector>
#include <limits>

Face3D::Face3D(std::vector<Vector3D*> points, Texture texture){
    this->points = points;
    Vector3D vec1 = *points.at(1) - *points.at(0);
    Vector3D vec2 = *points.at(2) - *points.at(0);
    this->normal = Vector3D::cross(vec1,vec2);
    this->texture = texture;
}

Face3D::Face3D(){};

Vector3D Face3D::middlePoint(){
    return (*points.at(0) + *points.at(1) + *points.at(2)) * (1.0/3.0);
}

std::ostream& operator<<(std::ostream& out, Face3D face){
    out << "Face : " << std::endl << "Normal : " << face.normal << std::endl;
    for(Vector3D* vec : face.points){
        out << *vec << std::endl;
    }
    return out;
}

float Face3D::minW(size_t dir){
    float min = std::numeric_limits<float>::max();
    for(Vector3D* v : this->points){
        if(v->at(dir) < min){
            min = v->at(dir);
        }
    } 
    return min;
}

float Face3D::maxW(size_t dir){
    float max = std::numeric_limits<float>::min();
    for(Vector3D* v : this->points){
        if(v->at(dir) > max){
            max = v->at(dir);
        }
    } 
    return max;
}

bool Face3D::smallerEqDir(Face3D* f1, Face3D* f2, size_t dir){
    /*
    if(f1->maxW(dir) < f2->minW(dir)){
        return true;
    }
    if(f2->maxW(dir) < f1->minW(dir)){
        return false;
    }
    if(f1->maxW(dir) < f2->maxW(dir) && f1->minW(dir) < f2->minW(dir)){
        return true;
    }
    if(f2->maxW(dir) < f1->maxW(dir) && f2->minW(dir) < f1->minW(dir)){
        return false;
    }*/
    return f1->middlePoint().at(dir) < f2->middlePoint().at(dir);
}