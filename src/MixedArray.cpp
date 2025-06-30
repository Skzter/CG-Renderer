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
    if(depth <= 0 || facesSize < 20){
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
    uint8_t bestdir;
    std::vector<Face3D*> bestleft;
    std::vector<Face3D*> bestright;
    BoundingBox bestleftB;
    BoundingBox bestrightB;
    float bestDisectVal;
    int optimize = INT_MAX;

    for(int dir = 0; dir < 3; dir++){
        BoundingBox leftB;
        BoundingBox rightB;

        leftB.p1 = box.p1;

        float disectValue = calcDisectValue(dir, faces, box, 0.2);
        
        leftB.p2 = box.p2;
        leftB.p2.at(dir) = disectValue;
        rightB.p1 = box.p1;
        rightB.p1.at(dir) = disectValue;
        rightB.p2 = box.p2;

        //std::cout << ", box p1: " << box.p1 << ", box p2: " << box.p2 << ": " << middlePoint << std::endl; 
        
        std::pair<std::vector<Face3D*>, std::vector<Face3D*>> disected = calcDisect(faces, dir, disectValue);

        int val = disected.first.size()+disected.second.size();
        if(val < optimize){
            bestleft = disected.first;
            bestright = disected.second;
            bestleftB = leftB;
            bestrightB = rightB;
            optimize = val;
            bestdir = dir;
            bestDisectVal = disectValue;
        }
    }
    this->Disects.push_back(Disect{
        bestDisectVal,
        bestdir,
        0,
        0
    });
    size_t pos = Disects.size() - 1;
    size_t left = buildArray(bestleft, bestleftB, depth-1);
    size_t right = buildArray(bestright, bestrightB, depth-1);
    
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


    if(std::fabs(ray.direction.at(disect.dir)) <= std::numeric_limits<float>::epsilon()){
        Hitpoint h1 = calcHP(ray, disect.left, lbox);
        Hitpoint h2 = calcHP(ray, disect.right, rbox);
        return h1.distance < h2.distance ? h1 : h2;
    }

    if(ray.direction.at(disect.dir) > 0) {
        Hitpoint h1 = calcHP(ray, disect.left, lbox);
        if (h1.face != NULL && h1.position.at(disect.dir) < disect.value) { //eigentlich müsste in alle Richtungen geclipt werdem, geht aber erstaml so
            return h1;
        }
        return calcHP(ray, disect.right, rbox);
    }else{
        Hitpoint h2 = calcHP(ray, disect.right, rbox);
        if (h2.face != NULL && h2.position.at(disect.dir) > disect.value) {
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
