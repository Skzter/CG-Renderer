#pragma once
#include "Vector3D.hpp"
#include <ostream>
#include <vector>
#include "Color.hpp"

class Face3D{
    std::vector<Vector3D*> points;
    Vector3D normal;
    Color color;

    public:
        Face3D();
        Face3D(std::vector<Vector3D*>);
        const std::vector<Vector3D*>& getPoints(){
            return (this->points);
        }
        const Color& getColor(){
            return this->color;
        }
        const Vector3D& getNormal(){
            return this->normal;
        }
};

std::ostream& operator<<(std::ostream& out, Face3D face);