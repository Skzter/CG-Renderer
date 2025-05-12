#include "../include/Vector3D.hpp"
#include <iostream>


Vector3D::Vector3D()
{
    X = 0;
    Y = 0;
    Z = 0;
}

Vector3D::Vector3D(float x, float y, float z)
{
    X = x;
    Y = y;
    Z = z;
}

void Vector3D::printPoint()
{
    std::cout << "[" << X << ", " << Y << ", " << Z << "]" << std::endl;
}

void Vector3D::setVector(float x, float y, float z)
{
    this->X = x;
    this->Y = y;
    this->Z = z;
}

/* ?????
Vector3D Vector3D::getPoint(Vector3D point)
{
    return point;
}
*/


void Vector3D::addVector(Vector3D point)
{
    this->X += point.X;
    this->Y += point.Y;
    this->Z += point.Z;
}

Vector3D Vector3D::operator+(const Vector3D&pointA)
{
    float x = this->X + pointA.X;
    float y = this->Y + pointA.Y;
    float z = this->Z + pointA.Z;
    return Vector3D(x,y,z);
}

Vector3D Vector3D::operator-(const Vector3D&pointA)
{
    float x = this->X - pointA.X;
    float y = this->Y - pointA.Y;
    float z = this->Z - pointA.Z;
    return Vector3D(x,y,z);
}

Vector3D Vector3D::cross(Vector3D& a, Vector3D& b){
    float x = a.getY() * b.getZ() - a.getZ() * b.getY();
    float y = a.getZ() * b.getX() - a.getX() * b.getZ();
    float z = a.getX() * b.getY() - a.getY() * b.getX();
    return Vector3D(x,y,z);
}

std::ostream& operator<<(std::ostream& out, Vector3D obj){
    return out << "[ " << obj.getX() << " | " << obj.getY() << " | " << obj.getZ() << " ]";
}



