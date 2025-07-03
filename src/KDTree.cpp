#include "../include/KDTree.hpp"
#include <algorithm>
#include <limits>

KDTree::KDTree(std::vector<Face3D*> faces, int maxDepth, BoundingBox box)
    : maxDepth(maxDepth) {
    root = build(faces, box, 0);
}

KDTree::~KDTree() {}

void KDTree::dealoc() {
    delete this;
}

std::unique_ptr<KDTree::Node> KDTree::build(std::vector<Face3D*>& faces, BoundingBox box, int depth) {
    auto node = std::make_unique<Node>();
    node->box = box;
    node->faces = faces;
    node->isLeaf = (depth >= maxDepth || faces.size() <= minFaces);
    if (node->isLeaf) {
        IBinaryDisect::sumFaces += faces.size();
        IBinaryDisect::cntLeafs++;
        if (faces.size() > IBinaryDisect::mostFaces) {
            IBinaryDisect::mostFaces = faces.size();
        }
        return node;
    }
    // Find best split axis (longest box axis)
    int axis = 0;
    float maxLen = box.p2.at(0) - box.p1.at(0);
    for (int i = 1; i < 3; ++i) {
        float len = box.p2.at(i) - box.p1.at(i);
        if (len > maxLen) {
            axis = i;
            maxLen = len;
        }
    }
    node->splitAxis = axis;
    // Find median value
    std::vector<float> centers;
    for (auto f : faces) {
        centers.push_back(f->middlePoint().at(axis));
    }
    std::nth_element(centers.begin(), centers.begin() + centers.size()/2, centers.end());
    float splitValue = centers[centers.size()/2];
    node->splitValue = splitValue;
    // Partition faces
    std::vector<Face3D*> leftFaces, rightFaces;
    for (auto f : faces) {
        if (f->middlePoint().at(axis) <= splitValue) leftFaces.push_back(f);
        else rightFaces.push_back(f);
    }
    // Create child boxes
    BoundingBox leftBox = box;
    BoundingBox rightBox = box;
    leftBox.p2.at(axis) = splitValue;
    rightBox.p1.at(axis) = splitValue;
    node->left = build(leftFaces, leftBox, depth+1);
    node->right = build(rightFaces, rightBox, depth+1);
    return node;
}

Hitpoint KDTree::closestHitpoint(Ray& ray) {
    return traverse(ray, root.get());
}

Hitpoint KDTree::traverse(Ray& ray, Node* node) {
    if (!node || !ray.check(node->box)) return Hitpoint();
    if (node->isLeaf) {
        Hitpoint closest;
        for (auto f : node->faces) {
            Hitpoint h = ray.check(*f);
            if (h.distance < closest.distance) closest = h;
        }
        return closest;
    }
    // Traverse children
    float rayVal = ray.origin.at(node->splitAxis);
    float dir = ray.direction.at(node->splitAxis);
    Node* first = (rayVal <= node->splitValue || dir == 0) ? node->left.get() : node->right.get();
    Node* second = (first == node->left.get()) ? node->right.get() : node->left.get();
    Hitpoint h1 = traverse(ray, first);
    if (h1.face != nullptr) return h1;
    return traverse(ray, second);
}
