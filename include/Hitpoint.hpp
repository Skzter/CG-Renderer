#pragma once 
#include "Vector3D.hpp"
#include "Object3D.hpp"
#include <limits>

class Hitpoint {
    public:
		Vector3D position = Vector3D();
		float distance = std::numeric_limits<float>::max();
		const Face3D* face = nullptr;

		Hitpoint();
		Hitpoint(Vector3D, float, Face3D*);
		~Hitpoint();
};

