#include "../include/BinaryArray.hpp"
#include <cmath>
#include <stack>
#include <vector>
#include <limits>
#include <iostream>

BinaryArray::BinaryArray(std::vector<Face3D*> faces, int maxDepth, BoundingBox box) {
    Leafs.resize(std::pow(2, maxDepth-1));

    cntDisects = std::pow(2, maxDepth-1)-1;
    this->disects = new float[this->cntDisects];
    depth = maxDepth;

    this->box = box;

    calcFace(faces, 0, 0, this->box);
}

void BinaryArray::calcFace(std::vector<Face3D*> faces, size_t pos, uint8_t dir, BoundingBox box) {
    if(pos >= cntDisects) {
        size_t leafIndex = pos - cntDisects;
        if(faces.size() > mostFaces){
            mostFaces = faces.size();
        }

        sumFaces += faces.size();
        cntLeafs++;

        Leafs[leafIndex] = faces;
        return;
    }

    float disectValue = calcDisectValue(dir, faces, box, 1);
    disects[pos] = disectValue;

    BoundingBox lbox = box;
    BoundingBox rbox = box;
    lbox.p2.at(dir) = disectValue;
    rbox.p1.at(dir) = disectValue;

    auto disect = calcDisect(faces, dir, disectValue);
    calcFace(disect.first, pos * 2 + 1, (dir + 1) % 3, lbox);
    calcFace(disect.second, pos * 2 + 2, (dir + 1) % 3, rbox);
}

Hitpoint BinaryArray::closestHitpoint(Ray& ray) {
    struct StackItem {
        size_t pos;
        size_t dir;
        BoundingBox box;
    };
    
    std::stack<StackItem> stack;
    stack.push({0, 0, this->box});
    
    while (!stack.empty()) {
        auto [pos, dir, box] = stack.top();
        stack.pop();
        
        if (!ray.check(box)) continue;
        
        if (pos >= this->cntDisects) {
            size_t leafIndex = pos - cntDisects;
            for (Face3D* face : Leafs[leafIndex]) {
                Hitpoint hit = ray.check(*face);
                if (hit.distance < std::numeric_limits<float>::max())
                    return hit;
            }
            continue;
        }

        
        // Push children in appropriate order
        float disectValue = disects[pos];
        BoundingBox lbox = box, rbox = box;
        lbox.p2.at(dir) = disectValue;
        rbox.p1.at(dir) = disectValue;
        
        if (ray.direction.at(dir) > 0) {
            stack.push({pos * 2 + 2, (dir + 1) % 3, rbox});
            stack.push({pos * 2 + 1, (dir + 1) % 3, lbox});
        } else {
            stack.push({pos * 2 + 1, (dir + 1) % 3, lbox});
            stack.push({pos * 2 + 2, (dir + 1) % 3, rbox});
        }
    }
    return Hitpoint();
}

void BinaryArray::dealoc() {
    delete disects;
    delete this;
}