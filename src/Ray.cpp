#include "../include/Ray.hpp"
#include <cmath>

Ray::Ray(Vector3D origin, Vector3D direction){
    this->origin = origin;
    this->direction = direction;
}

Hitpoint Ray::check(Face3D& face){
    //https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm

    constexpr float epsilon = std::numeric_limits<float>::epsilon();
    std::vector<Vector3D*> triangle = face.points;

    Vector3D edge1 = *triangle.at(2) - *triangle.at(0);
    Vector3D edge2 = *triangle.at(1) - *triangle.at(0);
    Vector3D ray_cross_e2 = Vector3D::cross(this->direction, edge2);
    float det = Vector3D::dot(edge1, ray_cross_e2);

    if (det > -epsilon && det < epsilon)
        return Hitpoint();    // This ray is parallel to this triangle.

    float inv_det = 1.0 / det;
    Vector3D s = this->origin - *triangle.at(0);
    float u = inv_det * Vector3D::dot(s, ray_cross_e2);

    if ((u < 0 && std::fabs(u) > epsilon) || (u > 1 && std::fabs(u-1) > epsilon))
        return Hitpoint();

    Vector3D s_cross_e1 = Vector3D::cross(s, edge1);
    float v = inv_det * Vector3D::dot(this->direction, s_cross_e1);

    if ((v < 0 && std::fabs(v) > epsilon) || (u + v > 1 && std::fabs(u + v - 1) > epsilon))
        return Hitpoint();

    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = inv_det * Vector3D::dot(edge2, s_cross_e1);

    if (t > epsilon) // ray intersection
    {
        Vector3D point = Vector3D(this->origin + this->direction * t);
        return Hitpoint(point, t, &face);
    }
    else // This means that there is a line intersection but not a ray intersection.
        return Hitpoint();
}

bool Ray::check(BoundingBox box){
    #define NUMDIM	3
    #define RIGHT	0
    #define LEFT	1
    #define MIDDLE	2

    bool inside = true;
	char quadrant[NUMDIM];
	register int i;
	int whichPlane;
	double maxT[NUMDIM];
	double candidatePlane[NUMDIM];

	/* Find candidate planes; this loop can be avoided if
   	rays cast all from the eye(assume perpsective view) */
	for (i=0; i<NUMDIM; i++)
		if(this->origin.at(i) < box.p1.at(i)) {
			quadrant[i] = LEFT;
			candidatePlane[i] = box.p1.at(i);
			inside = false;
		}else if (origin.at(i) > box.p2.at(i)) {
			quadrant[i] = RIGHT;
			candidatePlane[i] = box.p2.at(i);
			inside = false;
		}else	{
			quadrant[i] = MIDDLE;
		}

	/* Ray origin inside bounding box */
	if(inside)	{
		return (true);
	}


	/* Calculate T distances to candidate planes */
	for (i = 0; i < NUMDIM; i++)
		if (quadrant[i] != MIDDLE && direction.at(i) !=0.)
			maxT[i] = (candidatePlane[i]-origin.at(i)) / direction.at(i);
		else
			maxT[i] = -1.;

	/* Get largest of the maxT's for final choice of intersection */
	whichPlane = 0;
	for (i = 1; i < NUMDIM; i++)
		if (maxT[whichPlane] < maxT[i])
			whichPlane = i;

	/* Check final candidate actually inside box */
    Vector3D hp;
	if (maxT[whichPlane] < 0.) return (false);
	for (i = 0; i < NUMDIM; i++)
		if (whichPlane != i) {
			hp.at(i) = origin.at(i) + maxT[whichPlane] * direction.at(i);
			if (hp.at(i) < box.p1.at(i) || hp.at(i) > box.p2.at(i))
				return (false);
	return (true);				/* ray hits box */
}	
}
   