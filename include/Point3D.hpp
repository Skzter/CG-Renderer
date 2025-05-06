#pragma once

#include <iostream>

class Point3D
{
private:
    int X;
    int Y;
    int Z;

public:
    Point3D();
    Point3D(int x, int y, int z);
    void setPoint(int x, int y, int z);
    Point3D getPoint(Point3D point);
    void printPoint();
    void addPoint(Point3D point);
    Point3D operator+(const Point3D &pointA);
};

std::ostream& operator<<(std::ostream& os, const Point3D &pointA)
{
    // write obj to stream
    os << "[" << std::to_string(pointA->X) << ", " << std::to_string(pointA.Y) << ", " << std::to_string(pointA.Z) << "]";
    return os;
}
