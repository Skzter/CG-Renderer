#include "../include/MixedArray.hpp"
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <sys/types.h>

MixedArray::MixedArray(std::vector<Face3D*> faces, int maxDepth, BoundingBox box){
    this->box = box;
    this->buildArray(faces, box, maxDepth);
}

size_t MixedArray::buildArray(std::vector<Face3D*> faces,BoundingBox box, uint8_t depth){
    size_t facesSize = faces.size();
    if(depth <= 0 || facesSize < 30){
        IBinaryDisect::sumFaces+=facesSize;
        IBinaryDisect::cntLeafs++;
        if(facesSize > IBinaryDisect::mostFaces){
            IBinaryDisect::mostFaces = facesSize;
        }

        this->Leafs.push_back(faces);
        this->Disects.push_back(Disect{
            0,4,(ushort)(Leafs.size()-1), 0
        });
        return Disects.size() - 1;
    }

    //beste Teilung finden
    uint8_t axis = 0;
    float maxLen = box.p2.at(0) - box.p1.at(0);
    for (int i = 1; i < 3; ++i) {
        float len = box.p2.at(i) - box.p1.at(i);
        if (len > maxLen) {
            axis = i;
            maxLen = len;
        }
    }

    float splitValue = calcDisectValue(axis, faces);

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
        this->Disects.push_back(Disect{
        splitValue,
        axis,
        0,
        0
    });
    size_t pos = Disects.size() - 1;
    size_t left = buildArray(leftFaces, leftBox, depth-1);
    size_t right = buildArray(rightFaces, rightBox, depth-1);
    
    this->Disects.at(pos).left = left;
    this->Disects.at(pos).right = right;

    return pos;
}

Hitpoint MixedArray::closestHitpoint(Ray& ray){
    return this->calcHP(ray, 0, this->box);
}

Hitpoint MixedArray::calcHP(Ray& ray, ushort pos, BoundingBox box){
    if(!ray.check(box)) {
        return Hitpoint();
    }

    Disect disect = Disects.at(pos);
    if(disect.dir == 4){
        Hitpoint closest;
        for(Face3D* face : Leafs[disect.left]) {
            Hitpoint hit = ray.check(*face);
            if(hit.distance < closest.distance)
                closest = hit;
        }
        return closest;
    }

    BoundingBox lbox = box;
    BoundingBox rbox = box;
    float disectValue = disect.value;
    lbox.p2.at(disect.dir) = disectValue;
    rbox.p1.at(disect.dir) = disectValue;


    //if(std::fabs(ray.direction.at(disect.dir)) <= std::numeric_limits<float>::epsilon()){
        Hitpoint h1 = calcHP(ray, disect.left, lbox);
        Hitpoint h2 = calcHP(ray, disect.right, rbox);
        return h1.distance < h2.distance ? h1 : h2;
    //}

    if(ray.direction.at(disect.dir) > 0) {
        Hitpoint h1 = calcHP(ray, disect.left, lbox);
        if (h1.face != NULL && contains(box, h1.position)) { //eigentlich müsste in alle Richtungen geclipt werdem, geht aber erstaml so
            return h1;
        }
        return calcHP(ray, disect.right, rbox);
    }else{
        Hitpoint h2 = calcHP(ray, disect.right, rbox);
        if (h2.face != NULL && contains(box, h2.position)) {
            return h2;
        }
        return calcHP(ray, disect.left, lbox);
    }
    /*

    Hitpoint h1 = calcHP(ray, disect.left, lbox);
    Hitpoint h2 = calcHP(ray, disect.right, rbox);
    return h1.distance < h2.distance ? h1 : h2;
    */
}

void MixedArray::dealoc() {
    delete this;
}
