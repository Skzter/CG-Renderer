#include "../include/Point3D.hpp"
#include <iostream>
#include <string>


Point3D::Point3D()
{
    X = 0;
    Y = 0;
    Z = 0;
}

Point3D::Point3D(int x, int y, int z)
{
    X = x;
    Y = y;
    Z = z;
}

void Point3D::printPoint()
{
    std::cout << "[" << X << ", " << Y << ", " << Z << "]" << std::endl;
}

void Point3D::setPoint(int x, int y, int z)
{
    this->X = x;
    this->Y = y;
    this->Z = z;
}

Point3D Point3D::getPoint(Point3D point)
{
    return point;
}

void Point3D::addPoint(Point3D point)
{
    this->X += point.X;
    this->Y += point.Y;
    this->Z += point.Z;
}

Point3D Point3D::operator+(const Point3D &pointA)
{
    this->X += pointA.X;
    this->Y += pointA.Y;
    this->Z += pointA.Z;
    return Point3D(this->X,this->Y,this->Z);
}


