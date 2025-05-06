#pragma once

#include <vector>
//#include <SDL2/SDL.h>

#include "Camera.hpp"
#include "Light.hpp"
#include "Object.hpp"

class Scene
{
public:
    Scene();    
    std::vector<Object *> objects;
    std::vector<Light> lights;
    Camera camera;
};
