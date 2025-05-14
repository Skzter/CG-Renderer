#include "../include/Hitpoint.hpp"
#include <iostream>

Hitpoint::Hitpoint(){};

Hitpoint::Hitpoint(Vector3D position, float distance, Face3D* face){
    this->distance = distance;
    this->face = face;
    this->position = position;
}

Hitpoint::~Hitpoint(){
    //std::cout << "removing HP" << std::endl;
}