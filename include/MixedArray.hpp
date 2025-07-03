
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
    uint8_t dir; // höchstes bit 1 -> links blatt, 2. höchstes: rechts Blatt
    ushort left;
    //ushort middle;
    ushort right;
};

class MixedArray : public IBinaryDisect{
    BoundingBox box;
    std::vector<Disect> Disects;
    std::vector<std::vector<Face3D*>> Leafs;

    size_t buildArray(std::vector<Face3D*> faces, BoundingBox box, uint8_t depth);
    Hitpoint calcHP(Ray& ray, ushort pos, BoundingBox box);
    Hitpoint calcDisectHP(Ray&,ushort, BoundingBox, bool);

    public:
    MixedArray(const MixedArray&) = delete;
    MixedArray(std::vector<Face3D*> faces, int maxDepth, BoundingBox box);
    Hitpoint closestHitpoint(Ray&) override;
    void dealoc() override;
};