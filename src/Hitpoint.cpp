#pragma once 
#include "../include/Hitpoint.hpp"

Hitpoint::Hitpoint(Vector3D position, float distance, Object3D* Object){
    this->distance = distance;
    this->Object = Object;
    this->position = position;
}