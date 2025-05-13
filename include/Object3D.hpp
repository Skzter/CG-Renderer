#pragma once
#include "Vector3D.hpp"
#include "Face3D.hpp"
#include <ostream>
#include <vector>

class Object3D
{
    std::vector<Vector3D> points;
    std::vector<Face3D> faces;

    public:
        Object3D();
        Object3D(std::vector<Vector3D>, std::vector<std::vector<int>>);


        std::vector<Vector3D>& getPoints(){
            return (this->points);
        }

        std::vector<Face3D>& getFaces(){
            return (this->faces);
        }
};

std::ostream& operator<<(std::ostream& out, Object3D obj);
