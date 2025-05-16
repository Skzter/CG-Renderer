#pragma once
#include "Face3D.hpp"
#include "IBinaryDisect.hpp"
#include "BoundingBox.hpp"
#include <list>

class BinaryLinkedTree : public IBinaryDisect{
    public:
        virtual void dealoc();

        static BinaryLinkedTree* createNode(std::vector<Face3D*> faces, int maxDepth, BoundingBox box);

        static int mostFaces;
        static int sumFaces;
        static int cntLeafs;
    };

class BinaryNode : public BinaryLinkedTree{
    public:
        BoundingBox box;
        BinaryLinkedTree* left;
        BinaryLinkedTree* right;

        BinaryNode(BinaryLinkedTree* left, BinaryLinkedTree* right, BoundingBox box);
        Hitpoint closestHitpoint(Ray&);
        void dealoc() override;
};

class BinaryLeaf : public BinaryLinkedTree{
    public:
        std::vector<Face3D*> faces;

        BinaryLeaf(std::vector<Face3D*> faces);
        Hitpoint closestHitpoint(Ray&);
};

class BinaryEmpty : public BinaryLinkedTree{
    public:
        Hitpoint closestHitpoint(Ray&);
};