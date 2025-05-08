#pragma once

#include <iostream>

class Point3D
{
private:
    float X;
    float Y;
    float Z;

public:
    Point3D();
    Point3D(float x, float y, float z);
    void setPoint(float x, float y, float z);
    Point3D getPoint(Point3D point);
    void printPoint();
    void addPoint(Point3D point);
    Point3D scale(float factor); // Skalieren von Punkt
    Point3D operator+(const Point3D &pointA);
    float operator*(const Point3D &pointA); // Scalarprodukt
};
