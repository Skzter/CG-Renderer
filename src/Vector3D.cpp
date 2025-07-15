#include "../include/Vector3D.hpp"
#include <cstdint>
#include <iostream>
#include <cmath>
#include <limits>

Vector3D Vector3D::dirNorms[3] = {Vector3D(1,0,0),Vector3D(0,1,0),Vector3D(0,0,1)};

Vector3D Vector3D::minVector = Vector3D(std::numeric_limits<float>::min(),std::numeric_limits<float>::min(),std::numeric_limits<float>::min());

Vector3D Vector3D::maxVector = Vector3D(std::numeric_limits<float>::max(),std::numeric_limits<float>::max(),std::numeric_limits<float>::max());

Vector3D::Vector3D() : verts{0.0f, 0.0f, 0.0f} {}

Vector3D::Vector3D(float x, float y, float z)
{
    this->verts[0] = x;
    this->verts[1] = y;
    this->verts[2] = z;
}

void Vector3D::printPoint()
{
    std::cout << "[" << this->verts[0] << ", " << this->verts[1] << ", " << this->verts[2] << "]" << std::endl;
}

void Vector3D::setVector(float x, float y, float z)
{
    this->verts[0] = x;
    this->verts[1] = y;
    this->verts[2] = z;
}

/* ?????
Vector3D Vector3D::getPoint(Vector3D point)
{
    return point;
}
*/


void Vector3D::addVector(Vector3D point)
{
    this->verts[0] += point.verts[0];
    this->verts[1] += point.verts[1];
    this->verts[2] += point.verts[2];
}

Vector3D Vector3D::operator+(const Vector3D& point)
{
    float x = this->verts[0] + point.verts[0];
    float y = this->verts[1] + point.verts[1];
    float z = this->verts[2] + point.verts[2];
    return Vector3D(x,y,z);
}

Vector3D Vector3D::operator-(const Vector3D&point)
{
    float x = this->verts[0] - point.verts[0];
    float y = this->verts[1] - point.verts[1];
    float z = this->verts[2] - point.verts[2];
    return Vector3D(x,y,z);
}

Vector3D Vector3D::operator*(const float a)
{
    float x = this->verts[0] * a;
    float y = this->verts[1] * a;
    float z = this->verts[2] * a;
    return Vector3D(x,y,z);
}

float Vector3D::abs(){
    return std::sqrt(this->verts[0] * this->verts[0] + this->verts[1] * this->verts[1] + this->verts[2] * this->verts[2]);
}

bool Vector3D::operator==(Vector3D& other){
    const float epsilon = std::numeric_limits<float>::epsilon();
    for(uint8_t dim = 0; dim < 3; dim++){
        if(fabs(this->at(dim) - other.at(dim)) > epsilon){
            return false;
        }
    }
    return true;
}


float& Vector3D::at(size_t pos){
    return this->verts[pos];
}

Vector3D Vector3D::cross(Vector3D& a, Vector3D& b){
    float x = a.verts[1] * b.verts[2] - a.verts[2] * b.verts[1];
    float y = a.verts[2] * b.verts[0] - a.verts[0] * b.verts[2];
    float z = a.verts[0] * b.verts[1] - a.verts[1] * b.verts[0];
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

Vector3D Vector3D::normalize(Vector3D& a) {
    return Vector3D(a.getX()/a.abs(), a.getY()/a.abs(), a.getZ()/a.abs());
}
