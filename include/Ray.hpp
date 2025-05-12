#pragma once
#include "Vector3D.hpp"
#include "Hitpoint.hpp"

class Ray
{
    public:
	Vector3D origin;
	Vector3D direction;

	Ray(Vector3D, Vector3D);

	static Hitpoint check(Object3D);
};
