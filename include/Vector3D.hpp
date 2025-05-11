#pragma once

#include "Object3D.hpp"
#include <ostream>
class Vector3D
{
private:
    float X;
    float Y;
    float Z;

public:
    Vector3D();
    Vector3D(float x, float y, float z);
    void setVector(float x, float y, float z);
    //Vector3D getPoint(Vector3D point);
    void printPoint();
    void addVector(Vector3D point);
    Vector3D operator+(const Vector3D &pointA);

    float getX(){return this->X;}
    float getY(){return this->Y;}
    float getZ(){return this->Z;}
};

std::ostream& operator<<(std::ostream& out, Vector3D obj){
    return out << "[ " << obj.getX() << " | " << obj.getY() << " | " << obj.getZ() << " ]";
}

