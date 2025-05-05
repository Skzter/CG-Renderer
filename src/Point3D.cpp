#include "../include/Point3D.hpp"
#include <iostream>

Point3D::Point3D()
{
    X = 0;
    Y = 0;
    Z = 0;
}

void Point3D::printPoint()
{
    std::cout << "[" << X << ", " << Y << ", " << Z << "]" << std::endl;
}

void Point3D::setPoint(int x, int y, int z)
{
    X = x;
    Y = y;
    Z = z;
}

Point3D Point3D::getPoint(Point3D point)
{
    return point;
}
