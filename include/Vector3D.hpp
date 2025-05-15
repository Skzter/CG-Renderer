#pragma once
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
    Vector3D operator-(const Vector3D &pointA);
    Vector3D operator*(const float a);
    float abs();

    float getX(){return this->X;}
    float getY(){return this->Y;}
    float getZ(){return this->Z;}
    float& at(size_t);

    static Vector3D cross(Vector3D&, Vector3D&);
    static float dot(Vector3D&, Vector3D&);
    //static Vector3D middle(Vector3D&, Vector3D&);
};

std::ostream& operator<<(std::ostream& out, Vector3D obj);

