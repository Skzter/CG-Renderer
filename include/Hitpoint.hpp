#pragma once 
#include "Point3D.hpp"
#include "Object.hpp"

class Hitpoint {
    public :
	Point3D position ;
	float distance = std::numeric_limits <float >:: max ();
	const Object * object = nullptr ;
};
