#include "../include/Camera.hpp"

Camera::Camera(Vector3D eye, Vector3D view, float width, float height, int width_pixels, int height_pixels)
{
    this->eye = eye;
    this->view = view;
    this->width = width;
    this->height = height;
    this->width_pixels = width_pixels;
    this->height_pixels = height_pixels;
}

Camera::Camera(){}