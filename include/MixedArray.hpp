
#include "BoundingBox.hpp"
#include "Hitpoint.hpp"
#include "IBinaryDisect.hpp"
#include "Ray.hpp"
#include <cstddef>
#include <cstdint>
#include <sys/types.h>
#include <vector>

struct Disect{
    float value;
    uint8_t dir; // dir=4 -> Blatt
    ushort left; // wird zu position der faces, fals Blatt
    ushort right;
};

class MixedArray : public IBinaryDisect{
    BoundingBox box;
    std::vector<Disect> Disects;
    std::vector<std::vector<Face3D*>> Leafs;

    size_t buildArray(std::vector<Face3D*> faces, BoundingBox box, uint8_t depth);
    Hitpoint calcHP(Ray& ray, ushort pos, BoundingBox box);

    public:
    MixedArray(const MixedArray&) = delete;
    MixedArray(std::vector<Face3D*> faces, int maxDepth, BoundingBox box);
    Hitpoint closestHitpoint(Ray&) override;
    void dealoc() override;
};