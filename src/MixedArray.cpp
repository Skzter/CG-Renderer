#include "../include/MixedArray.hpp"
#include <cstddef>
#include <cstdint>
#include <sys/types.h>
#include <vector>

#define MINFACES 10
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

    
    std::vector<Face3D*> leftFaces, rightFaces;
    // Compute initial child boxes
    
    // Assign faces by centroid
    for (auto f : faces) {
        if (f->middlePoint().at(axis) <= splitValue) leftFaces.push_back(f);
        else rightFaces.push_back(f);
    }
   
    BoundingBox leftBox;
    // Expand child boxes to fully contain all assigned faces
    if(!leftFaces.empty()){
        leftBox = leftFaces[0]->boundingBox();
        for (size_t i = 1; i < leftFaces.size(); ++i) {
            leftBox.expandToInclude(leftFaces[i]->boundingBox());
        }
    }   
 
    BoundingBox rightBox;
    if(!rightFaces.empty()){
        rightBox = rightFaces[0]->boundingBox();
        for (size_t i = 1; i < rightFaces.size(); ++i) {
            rightBox.expandToInclude(rightFaces[i]->boundingBox());
        }
    }

    this->Disects.push_back(Disect{
        axis,
        0,
        0,
        leftBox,
        rightBox,
    });
    size_t left,right,pos = Disects.size() - 1;

    if(leftFaces.size() < MINFACES || depth <= 0){
        this->Disects.at(pos).dir |= LEFTLEAF;
        this->Leafs.push_back(leftFaces);
        left = this->Leafs.size() - 1;
        IBinaryDisect::incrCounters(leftFaces.size());
    }else{
        left = buildArray(leftFaces, leftBox, depth-1);
    }

    if(rightFaces.size() < MINFACES || depth <= 0){
        this->Disects.at(pos).dir |= RIGHTLEAF;
        this->Leafs.push_back(rightFaces);
        right = this->Leafs.size() - 1;
        IBinaryDisect::incrCounters(rightFaces.size());
    }else{
        right = buildArray(rightFaces, rightBox, depth-1);
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

    BoundingBox lbox = disect.leftB;
    BoundingBox rbox = disect.rightB;

    
    if(ray.direction.at(disect.dir & 0b00000011) > 0) {
        Hitpoint h1 = calcDisectHP(ray, disect.left, lbox, disect.dir & LEFTLEAF);
        if (h1.face != NULL && !rbox.contains(h1.position)) { //eigentlich müsste in alle Richtungen geclipt werdem, geht aber erstaml so
            return h1;
        }
        Hitpoint h2 = calcDisectHP(ray, disect.right, rbox, disect.dir & RIGHTLEAF);
        return h1.distance < h2.distance ? h1 : h2;
    }else{
        Hitpoint h2 = calcDisectHP(ray, disect.right, rbox, disect.dir & RIGHTLEAF);
        if (h2.face != NULL && !lbox.contains(h2.position)) { //eigentlich müsste in alle Richtungen geclipt werdem, geht aber erstaml so
            return h2;
        }
        Hitpoint h1 = calcDisectHP(ray, disect.left, lbox, disect.dir & LEFTLEAF);
        return h1.distance < h2.distance ? h1 : h2;
    }
    
    
    //Hitpoint h1 = calcDisectHP(ray, disect.left, lbox, disect.dir & LEFTLEAF);
    //Hitpoint h2 = calcDisectHP(ray, disect.right, rbox, disect.dir & RIGHTLEAF);
    //return h1.distance < h2.distance ? h1 : h2;
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
