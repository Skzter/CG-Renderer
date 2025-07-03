#include "../include/MixedArray.hpp"
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <sys/types.h>
#include <vector>

#define MINFACES 20
#define LEFTLEAF 0b10000000
#define RIGHTLEAF 0b01000000
#define AXES 0b00000011

MixedArray::MixedArray(std::vector<Face3D*> faces, int maxDepth, BoundingBox box){
    this->box = box;
    this->buildArray(faces, box, maxDepth);
}

size_t MixedArray::buildArray(std::vector<Face3D*> faces,BoundingBox box, uint8_t depth){
    IBinaryDisect::cntLeafs++;
    /*size_t facesSize = faces.size();
    if(depth <= 0 || facesSize < MINFACES){
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
    }*/

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

    /*
    std::vector<Face3D*> leftFaces, rightFaces;
    for (auto f : faces) {
        if (f->middlePoint().at(axis) <= splitValue) leftFaces.push_back(f);
        else rightFaces.push_back(f);first
    }
    */

    std::pair<std::vector<Face3D*>, std::vector<Face3D*>> disfaces = calcDisect(faces, axis, splitValue);

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
    size_t left,right,pos = Disects.size() - 1;

    if(disfaces.first.size() < MINFACES || depth <= 0){
        this->Disects.at(pos).dir |= LEFTLEAF;
        this->Leafs.push_back(disfaces.first);
        left = this->Leafs.size() - 1;
        IBinaryDisect::incrCounters(disfaces.first.size());
    }else{
        left = buildArray(disfaces.first, leftBox, depth-1);
    }

    if(disfaces.second.size() < MINFACES || depth <= 0){
        this->Disects.at(pos).dir |= RIGHTLEAF;
        this->Leafs.push_back(disfaces.second);
        right = this->Leafs.size() - 1;
        IBinaryDisect::incrCounters(disfaces.second.size());
    }else{
        right = buildArray(disfaces.second, rightBox, depth-1);
    }

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
    /*
    if(disect.dir == 4){
        Hitpoint closest;
        for(Face3D* face : Leafs[disect.left]) {
            Hitpoint hit = ray.check(*face);
            if(hit.distance < closest.distance)
                closest = hit;
        }
        return closest;
    }*/

    BoundingBox lbox = box;
    BoundingBox rbox = box;
    float disectValue = disect.value;
    lbox.p2.at(disect.dir & AXES) = disectValue;
    rbox.p1.at(disect.dir & AXES) = disectValue;

    if(ray.direction.at(disect.dir & 0b00000011) > 0) {
        Hitpoint h1 = calcDisectHP(ray, disect.left, lbox, disect.dir & LEFTLEAF);
        if (h1.face != NULL && contains(lbox, h1.position)) { //eigentlich müsste in alle Richtungen geclipt werdem, geht aber erstaml so
            return h1;
        }
        return calcDisectHP(ray, disect.right, rbox, disect.dir & RIGHTLEAF);
    }else{
        Hitpoint h2 = calcDisectHP(ray, disect.right, rbox, disect.dir & RIGHTLEAF);
        if (h2.face != NULL && contains(rbox, h2.position)) { //eigentlich müsste in alle Richtungen geclipt werdem, geht aber erstaml so
            return h2;
        }
        return calcDisectHP(ray, disect.left, lbox, disect.dir & LEFTLEAF);
    }
}

void MixedArray::dealoc() {
    delete this;
}

Hitpoint MixedArray::calcDisectHP(Ray& ray, ushort disectSide, BoundingBox box, bool isLeaf){
    Hitpoint HP;
    if(isLeaf){
        //std::cout << "side: " << disectSide << std::endl;
        if(ray.check(box)){
            for(Face3D* face : Leafs[disectSide]) {
                Hitpoint hit = ray.check(*face);
                if(hit.distance < HP.distance)
                    HP = hit;
            }
        }  
    }else{
        HP = calcHP(ray, disectSide, box);
    }
    return HP;
}
