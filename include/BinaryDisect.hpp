#pragma once
#include "Face3D.hpp"
#include "Hitpoint.hpp"
#include "Ray.hpp"
#include "BoundingBox.hpp"
#include "IBinaryDisect.hpp"
#include <cstdint>
#include <vector>

class BinaryDisect : public IBinaryDisect{
    public:
        static BinaryDisect* createNode(std::vector<Face3D*> faces, int maxDepth, BoundingBox box);
        virtual void dealoc();
};

class BinaryNode : public BinaryDisect{
    public:
        BoundingBox box;
        BinaryDisect* left;
        BinaryDisect* right;
        uint8_t dir;

        BinaryNode(BinaryDisect* left, BinaryDisect* right, BoundingBox box, uint8_t dir);
        Hitpoint closestHitpoint(Ray&) override;
        void dealoc() override;
};

class BinaryLeaf : public BinaryDisect{
    public:
        std::vector<Face3D*> faces;

        BinaryLeaf(std::vector<Face3D*> faces);
        Hitpoint closestHitpoint(Ray&) override;
};