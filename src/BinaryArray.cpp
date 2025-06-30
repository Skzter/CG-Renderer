#include "../include/BinaryArray.hpp"
#include <cmath>
#include <cstddef>
#include <stack>
#include <vector>
#include <limits>
#include <iostream>

BinaryArray::BinaryArray(std::vector<Face3D*> faces, int maxDepth, BoundingBox box) {
    Leafs.resize(std::pow(2, maxDepth-1));

    this->depth = maxDepth;

    cntDisects = std::pow(2, maxDepth-1)-1;
    this->disects = new float[this->cntDisects];

    this->box = box;

    calcFace(faces, 0, 0, this->box, 1);
}

void BinaryArray::calcFace(std::vector<Face3D*> faces, size_t pos, uint8_t dir, BoundingBox box, size_t curDepth) {
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

    if(faces.size() < 8){
        this->disects[pos] = std::numeric_limits<float>::max();
        size_t newpos = std::pow(2, this->depth - curDepth - 1) * pos;
        //std::cout << "Früher rausgehen: " << newpos+1 << " (max: " << this->cntDisects << "), old: " << pos << "\ncurDepth: " << curDepth << " maxdepth: " << this->depth << std::endl;
        this->Leafs[newpos+1] = faces;
        return;
    }

    float disectValue = calcDisectValue(dir, faces, box, 0.2);
    disects[pos] = disectValue;

    BoundingBox lbox = box;
    BoundingBox rbox = box;
    lbox.p2.at(dir) = disectValue;
    rbox.p1.at(dir) = disectValue;

    auto disect = calcDisect(faces, dir, disectValue);
    calcFace(disect.first, pos * 2 + 1, (dir + 1) % 3, lbox, curDepth+1);
    calcFace(disect.second, pos * 2 + 2, (dir + 1) % 3, rbox, curDepth+1);
}

Hitpoint BinaryArray::closestHitpoint(Ray& ray) {
    /*
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
    */
    return calcHP(0, ray, 0, this->box, 1);
}

Hitpoint BinaryArray::calcHP(size_t pos, Ray& ray, size_t dir, BoundingBox box, size_t curDepth) {
    if(!ray.check(box)) {
        return Hitpoint();
    }

    if(pos >= this->cntDisects) {
        Hitpoint closest;
        size_t leafIndex = pos - cntDisects;
        for(Face3D* face : Leafs[leafIndex]) {
            Hitpoint hit = ray.check(*face);
            if(hit.distance < closest.distance)
                closest = hit;
        }
        return closest;
    }

    if(disects[pos] == std::numeric_limits<float>::max()){
        size_t newpos = std::pow(2, this->depth - curDepth - 1) * pos;

        //std::cout << "Früher rausgehen: " << newpos+1 << " (max: " << this->cntDisects << "), old: " << pos << "\ncurDepth: " << curDepth << " maxdepth: " << this->depth << std::endl;

        Hitpoint closest = Hitpoint();
        for(Face3D* f : this->Leafs[newpos]){
            Hitpoint hp = ray.check(*f);
            if(hp.distance < closest.distance){
                closest = hp;
            }
        }
        return closest;
    }

    BoundingBox lbox = box;
    BoundingBox rbox = box;
    float disectValue = disects[pos];
    lbox.p2.at(dir) = disectValue;
    rbox.p1.at(dir) = disectValue;

    if(ray.direction.at(dir) > 0) {
        Hitpoint h1 = calcHP(pos * 2 + 1, ray, (dir + 1) % 3, lbox, curDepth+1);
        if (h1.distance < std::numeric_limits<float>::max()) {
            return h1;
        }
        return calcHP(pos * 2 + 2, ray, (dir + 1) % 3, rbox,curDepth+1);
    } else {
        Hitpoint h2 = calcHP(pos * 2 + 2, ray, (dir + 1) % 3, rbox,curDepth+1);
        if (h2.distance < std::numeric_limits<float>::max()) {
            return h2;
        }
        return calcHP(pos * 2 + 1, ray, (dir + 1) % 3, lbox,curDepth+1);
    }
}

void BinaryArray::dealoc() {
    delete disects;
    delete this;
}