#include "../include/Light.hpp"

Light::Light(Vector3D a, float half, Color col) {
    this->sourcePoint = a;
    this->distToHalfBrighness = half;
    this->color = col;
}

Vector3D Light::getLightSource() {
    return this->sourcePoint;
}

float Light::fallof(){
    return this->distToHalfBrighness;
}

Color Light::getColor(){
    return this->color;
}
