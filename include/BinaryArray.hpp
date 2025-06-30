#include "Face3D.hpp"
#include "Hitpoint.hpp"
#include "Ray.hpp"
#include "IBinaryDisect.hpp"
#include <cstddef>
#include <cstdint>
#include <vector>
#include <array>
class BinaryArray : public IBinaryDisect{
    private:
        size_t depth;
        BoundingBox box;

        std::vector<std::vector<Face3D*>> Leafs;

        float* disects;
        size_t cntDisects;

        void calcFace(std::vector<Face3D*> faces, size_t pos, uint8_t dir, BoundingBox box, size_t curDepth);
        Hitpoint calcHP(size_t pos, Ray& ray, size_t dir, BoundingBox box, size_t curDepth);
    public:
        BinaryArray(const BinaryArray&) = delete;
        BinaryArray(std::vector<Face3D*> faces, int maxDepth, BoundingBox box);
        //~BinaryArray();
        Hitpoint closestHitpoint(Ray&) override;
        void dealoc() override;

        //BinaryArray& operator=(const BinaryArray&) = delete;
};
