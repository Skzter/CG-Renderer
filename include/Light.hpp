#pragma once

#include "Color.hpp"
#include "Vector3D.hpp"
class Light
{
    private:
	Vector3D sourcePoint;
	float distToHalfBrighness;
	Color color;

    public:
	Light(Vector3D, float, Color);
	Vector3D getLightSource();
	Color getColor();
	float fallof();
};
