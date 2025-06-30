#pragma once

#include "Vector3D.hpp"
class Light
{
    private:
	Vector3D sourcePoint;

    public:
	Light(Vector3D);
	Vector3D getLightSource();
};
