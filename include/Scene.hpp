#pragma once
#include <istream>
#include <vector>
#include "BoundingBox.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Object3D.hpp"
#include "BinaryDisect.hpp"
#include <mutex>

class Scene
{
public: 
    Scene();
    std::vector<Object3D> Object3Ds;
    std::vector<Light> lights;
    Camera camera;
    IBinaryDisect* disect;
    BoundingBox box;


    int progress;
    std::mutex proglock;

    void loadFile(std::istream&,int);
    void drawPicture();
    void testoptimized(uint);
    void calcPixels(size_t, size_t, float, float, uint8_t*, Vector3D);
};
