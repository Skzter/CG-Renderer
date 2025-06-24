#include "Face3D.hpp"
#include "Hitpoint.hpp"
#include "Ray.hpp"
#include "IBinaryDisect.hpp"
#include <cstddef>
#include <vector>
class BinaryArray : public IBinaryDisect{
    private:
        size_t length;
        Face3D** faces;
        float* disects;
        void calcFace(int pos, int dir);
    public:
        BinaryArray(std::vector<Face3D*> faces, int maxDepth, BoundingBox box);
        Hitpoint closestHitpoint(Ray&) override;
        void dealoc() override;
};