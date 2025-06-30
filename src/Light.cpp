#include "../include/Light.hpp"

Light::Light(Vector3D a) {
    this->sourcePoint = a;
}

Vector3D Light::getLightSource() {
    return this->sourcePoint;
}
