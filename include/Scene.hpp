#pragma once

#include <istream>
#include <vector>
//#include <SDL2/SDL.h>

#include "Camera.hpp"
#include "Light.hpp"
#include "Object3D.hpp"

class Scene
{
public:
    Scene();    
    std::vector<Object3D *> Object3Ds;
    std::vector<Light> lights;
    Camera camera;

    void loadFile(std::istream*);
};
