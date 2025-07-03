#pragma once
#include <ostream>

class Vector3D
{
private:
    float verts[3] = {0,0,0};

public:
    Vector3D();
    Vector3D(float x, float y, float z);
    void setVector(float x, float y, float z);
    //Vector3D getPoint(Vector3D point);
    void printPoint();
    void addVector(Vector3D point);
    Vector3D operator+(const Vector3D &point);
    Vector3D operator-(const Vector3D &point);
    Vector3D operator*(const float a);
    float abs();
    bool operator==(Vector3D& other);

    float getX(){return this->verts[0];}
    float getY(){return this->verts[1];}
    float getZ(){return this->verts[2];}
    float& at(size_t);

    static Vector3D dirNorms[3];
    static Vector3D minVector;
    static Vector3D maxVector;

    static Vector3D cross(Vector3D&, Vector3D&);
    static float dot(Vector3D&, Vector3D&);
    static Vector3D normalize(Vector3D&);

    //static Vector3D middle(Vector3D&, Vector3D&);
};

std::ostream& operator<<(std::ostream& out, Vector3D obj);

