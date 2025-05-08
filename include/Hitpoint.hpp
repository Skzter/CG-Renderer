#pragma once 
#include "Point3D.hpp"
#include "Object3D.hpp"
#include <limits>

class Hitpoint {
    public :
	Point3D position ;
	float distance = std::numeric_limits <float >:: max ();
	const Object3D * Object3D = nullptr ;
};
