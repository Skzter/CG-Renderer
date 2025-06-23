#pragma once
#include "Face3D.hpp"
#include "IBinaryDisect.hpp"
#include "BoundingBox.hpp"
#include "Vector3D.hpp"
#include <cstdint>
#include <list>

class BinaryLinkedTree : public IBinaryDisect{
    public:
        static BinaryLinkedTree* createNode(std::vector<Face3D*> faces, int maxDepth, BoundingBox box);

        static int mostFaces;
        static int sumFaces;
        static int cntLeafs;
        static int duplicate;
    };

class BinaryNode : public BinaryLinkedTree{
    public:
        BoundingBox box;
        BinaryLinkedTree* left;
        BinaryLinkedTree* right;
        uint8_t dir;

        BinaryNode(BinaryLinkedTree* left, BinaryLinkedTree* right, BoundingBox box, uint8_t dir);
        Hitpoint closestHitpoint(Ray&) override;
        void dealoc() override;
};

class BinaryLeaf : public BinaryLinkedTree{
    public:
        std::vector<Face3D*> faces;

        BinaryLeaf(std::vector<Face3D*> faces);
        Hitpoint closestHitpoint(Ray&) override;
        void dealoc() override;
};

class BinaryEmpty : public BinaryLinkedTree{
    public:
        Hitpoint closestHitpoint(Ray&) override;
        void dealoc() override;
};