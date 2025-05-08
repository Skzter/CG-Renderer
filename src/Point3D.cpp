#include "../include/Point3D.hpp"
#include <iostream>
#include <string>


Point3D::Point3D()
{
    X = 0;
    Y = 0;
    Z = 0;
}

Point3D::Point3D(float x, float y, float z)
{
    X = x;
    Y = y;
    Z = z;
}

void Point3D::printPoint()
{
    std::cout << "[" << X << ", " << Y << ", " << Z << "]" << std::endl;
}

void Point3D::setPoint(float x, float y, float z)
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

Point3D Point3D::scale(float factor)
{
    this->X *= factor;
    this->Y *= factor;
    this->Z *= factor;
    return Point3D(this->X, this->Y, this->Z);
}

Point3D Point3D::operator+(const Point3D &pointA)
{
    this->X += pointA.X;
    this->Y += pointA.Y;
    this->Z += pointA.Z;
    return Point3D(this->X,this->Y,this->Z);
}

float Point3D::operator*(const Point3D &pointA)
{
    float dotproduct = (this->X * pointA.X) + (this->Y * pointA.Y) + (this->Z * pointA.Z); 
    return dotproduct;
}
