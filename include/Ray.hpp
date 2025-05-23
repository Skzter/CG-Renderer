#pragma once
#include "Vector3D.hpp"
#include "Hitpoint.hpp"
#include "BoundingBox.hpp"

class Ray
{
    public:
	Vector3D origin;
	Vector3D direction;

	Ray(Vector3D, Vector3D);

	Hitpoint check(Face3D&);
	bool check(BoundingBox);
};
