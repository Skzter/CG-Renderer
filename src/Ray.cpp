#include "../include/Ray.hpp"
#include <cmath>

Ray::Ray(Vector3D origin, Vector3D direction){
    this->origin = origin;
    this->direction = direction;
}

Hitpoint Ray::check(Face3D face){
    //https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm

    constexpr float epsilon = std::numeric_limits<float>::epsilon();
    std::vector<Vector3D*> triangle = face.points;

    Vector3D edge1 = *triangle.at(1) - *triangle.at(0);
    Vector3D edge2 = *triangle.at(2) - *triangle.at(0);
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
        return Hitpoint(point, this->direction.abs() * t, &face);
    }
    else // This means that there is a line intersection but not a ray intersection.
        return Hitpoint();
}
   