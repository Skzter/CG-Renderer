#pragma once 
#include "Vector3D.hpp"
#include "Object3D.hpp"
#include <limits>

class Hitpoint {
    public :
	Vector3D position ;
	float distance = std::numeric_limits <float >:: max ();
	const Object3D * Object3D = nullptr ;
};
