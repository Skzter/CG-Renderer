#pragma once
#include <array>
#include <chrono>
#include <istream>
#include <vector>
#include "BoundingBox.hpp"
#include "Camera.hpp"
#include "Face3D.hpp"
#include "Light.hpp"
#include "Object3D.hpp"
#include "BinaryDisect.hpp"
#include "KDTree.hpp"
#include "MixedArray.hpp"
#include "BinaryArray.hpp"
#include "Vector3D.hpp"
#include <mutex>

using tp = std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<long, std::ratio<1, 1000000000>>>;

class Scene
{
private:
    bool graphics = false;
    int progress;
    std::mutex proglock;

public: 
    Scene(std::istream& file, int depth);
    std::vector<Object3D> Object3Ds;
    std::vector<Light> lights;
    Camera camera;
    IBinaryDisect* disect;
    BoundingBox box;

    std::array<Texture, 6> texture = {};

    void loadFile(std::istream&,int);
    void drawPicture();
    void testoptimized(uint, tp);
    void calcPixels(size_t, size_t, Vector3D, Vector3D, uint8_t*, Vector3D, tp);
    void loadGraphics(std::array<std::string,6>);
};
