#include "../include/Vector3D.hpp"
#include <iostream>
#include <cmath>

Vector3D::Vector3D()
{
    cords[0] = 0;
    cords[1] = 0;
    cords[2] = 0;
}

Vector3D::Vector3D(float x, float y, float z)
{
    cords[0] = x;
    cords[1] = y;
    cords[2] = z;
}

void Vector3D::printPoint()
{
    std::cout << "[" << cords[0] << ", " << cords[1] << ", " << cords[2] << "]" << std::endl;
}

void Vector3D::setVector(float x, float y, float z)
{
    this->cords[0] = x;
    this->cords[1] = y;
    this->cords[2] = z;
}

/* ?????
Vector3D Vector3D::getPoint(Vector3D point)
{
    return point;
}
*/


void Vector3D::addVector(Vector3D point)
{
    this->cords[0] += point.cords[0];
    this->cords[1] += point.cords[1];
    this->cords[2] += point.cords[2];
}

Vector3D Vector3D::operator+(const Vector3D&pointA)
{
    float x = this->cords[0] + pointA.cords[0];
    float y = this->cords[1] + pointA.cords[1];
    float z = this->cords[2] + pointA.cords[2];
    return Vector3D(x,y,z);
}

Vector3D Vector3D::operator-(const Vector3D&pointA)
{
    float x = this->cords[0] - pointA.cords[0];
    float y = this->cords[1] - pointA.cords[1];
    float z = this->cords[2] - pointA.cords[2];
    return Vector3D(x,y,z);
}

Vector3D Vector3D::operator*(const float a)
{
    float x = this->cords[0] * a;
    float y = this->cords[1] * a;
    float z = this->cords[2] * a;
    return Vector3D(x,y,z);
}

float Vector3D::abs(){
    return std::sqrt(this->cords[0] * this->cords[0] + this->cords[1] * this->cords[1] + this->cords[2] * this->cords[2]);
}

float& Vector3D::at(size_t pos){
    return cords[pos];
}

Vector3D Vector3D::cross(Vector3D& a, Vector3D& b){
    float x = a.getY() * b.getZ() - a.getZ() * b.getY();
    float y = a.getZ() * b.getX() - a.getX() * b.getZ();
    float z = a.getX() * b.getY() - a.getY() * b.getX();
    return Vector3D(x,y,z);
}

Vector3D middle(Vector3D& a, Vector3D& b){
    return (a + b) * 0.5; 
}

float Vector3D::dot(Vector3D& a, Vector3D& b){
    return a.getX() * b.getX() + a.getY() * b.getY() + a.getZ() * b.getZ();
}
std::ostream& operator<<(std::ostream& out, Vector3D obj){
    return out << "[ " << obj.getX() << " | " << obj.getY() << " | " << obj.getZ() << " ]";
}




