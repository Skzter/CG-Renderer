#pragma once

class Vector3D
{
private:
    float X;
    float Y;
    float Z;

public:
    Vector3D();
    Vector3D(float x, float y, float z);
    void setPoint(float x, float y, float z);
    Vector3D getPoint(Vector3D point);
    void printPoint();
    void addPoint(Vector3D point);
    Vector3D operator+(const Vector3D &pointA);
};

