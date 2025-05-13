#pragma once
#include "Face3D.hpp"
#include "Hitpoint.hpp"
#include "Ray.hpp"
#include "BoundingBox.hpp"
#include <list>

class BinaryDisect{
    
    public:
        bool empty;
        virtual Hitpoint closestHitpoint(Ray&) = 0;

        static BinaryDisect* createNode(std::vector<Face3D*> faces, int maxDepth, BoundingBox box);
};

class BinaryNode : public BinaryDisect{
    public:
        BoundingBox box;
        BinaryDisect* left;
        BinaryDisect* right;

        BinaryNode(BinaryDisect* left, BinaryDisect* right, BoundingBox box);
        Hitpoint closestHitpoint(Ray&);

        static std::list<BinaryNode> allN;
};

class BinaryLeaf : public BinaryDisect{
    public:
        std::vector<Face3D*> faces;

        BinaryLeaf(std::vector<Face3D*> faces);
        Hitpoint closestHitpoint(Ray&);

        static std::list<BinaryLeaf> allL;
};