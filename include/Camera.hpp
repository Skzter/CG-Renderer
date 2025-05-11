#pragma once 
#include "Vector3D.hpp"
#include "Ray.hpp"

class Camera{
    public :
	Vector3D eye;
	Vector3D view ; // direction vector from the eye to the center of the screen 6 
	float width ; // width in world coordinates of one pixel on the screen 7 
	float height ; // height in world coordinates of one pixel on the screen 8 
	int width_pixels ; // number of pixels on the screen in the horizontal direction 9 
	int height_pixels ; // number of pixels on the screen in the vertical direction
	Vector3D get_pixel(int x, int y) const;
	Ray get_ray(int x, int y) const;
};
