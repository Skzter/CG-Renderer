#pragma once
#include "IBinaryDisect.hpp"
#include <vector>
#include "Face3D.hpp"
#include "BoundingBox.hpp"
#include <memory>

class KDTree : public IBinaryDisect {
public:
    KDTree(std::vector<Face3D*> faces, int maxDepth, BoundingBox box);
    Hitpoint closestHitpoint(Ray&) override;
    void dealoc() override;
    ~KDTree();

private:
    struct Node {
        BoundingBox box;
        std::vector<Face3D*> faces;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        int splitAxis = -1;
        float splitValue = 0.0f;
        bool isLeaf = false;
    };

    std::unique_ptr<Node> root;
    int maxDepth;
    size_t minFaces = 10;

    std::unique_ptr<Node> build(std::vector<Face3D*>& faces, BoundingBox box, int depth);
    Hitpoint traverse(Ray& ray, Node* node);
};
