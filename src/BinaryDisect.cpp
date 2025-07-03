#include "../include/BinaryDisect.hpp"
#include <climits>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>

#include <utility>
#include <vector>

void BinaryDisect::dealoc(){
    //std::cout << "deleting smth else" << std::endl;
     delete this;
}

BinaryNode::BinaryNode(BinaryDisect* left, BinaryDisect* right, BoundingBox box, uint8_t dir){
    this->left = left;
    this->right = right;
    this->box = box;
    this->dir = dir;
}

void BinaryNode::dealoc(){
    //std::cout << "deleting Node" << std::endl;
    this->left->dealoc();
    this->right->dealoc();
    delete this;
}

Hitpoint BinaryNode::closestHitpoint(Ray& ray){
    if(!ray.check(this->box)){
        //std::cout << "missed Box" << std::endl;
        return Hitpoint();
    }

     if(Vector3D::dot(ray.direction, Vector3D::dirNorms[this->dir]) > 0){
        Hitpoint h1 = this->left->closestHitpoint(ray);
        if (h1.distance < std::numeric_limits<float>::max()){
            return h1;
        }
        return this->right->closestHitpoint(ray);
     }else{
        Hitpoint h2 = this->right->closestHitpoint(ray);
        if (h2.distance < std::numeric_limits<float>::max()){
            return h2;
        }
        return this->left->closestHitpoint(ray);
     }
}


Hitpoint BinaryLeaf::closestHitpoint(Ray& ray){
    Hitpoint closest = Hitpoint();
    for(Face3D* face : this->faces){
        Hitpoint hit = ray.check(*face);
        if(hit.distance < closest.distance)
            closest = hit;
    }
    //std::cout << closest.position << std::endl;
    return closest;
}

BinaryLeaf::BinaryLeaf(std::vector<Face3D*> faces){
    this->faces = faces;

    sumFaces += faces.size();
    cntLeafs++;
    //if(faces.size() != 0)
    //std::cout << "Num Faces: " << faces.size() << std::endl;
    if(faces.size() > mostFaces){
        mostFaces = faces.size();
    }
}

BinaryDisect* BinaryDisect::createNode(std::vector<Face3D*> faces, int depth, BoundingBox box){
    //https://www.geeksforgeeks.org/quickselect-algorithm/
    //auch mal mit zugriff auf Punkte mit at() n bissl übersichtlicher machen

    if(depth-- <= 0 || faces.size() < 10){
        return new BinaryLeaf(faces);
    }
    
    //std::vector<Face3D*> left;
    //::vector<Face3D*> right;

    /*
    size_t dir;
    float xdiff = fabs(box.p1.getX() - box.p2.getX());
    float ydiff = fabs(box.p1.getY() - box.p2.getY());
    float zdiff = fabs(box.p1.getZ() - box.p2.getZ());
   
    if(xdiff > ydiff){
        if(xdiff > zdiff){
            dir = 0;
        }else{
            dir = 2;
        }
    }else{
        if(ydiff > zdiff){
            dir = 1;
        }else{
            dir = 2;
        }
    }
    */
    //std::cout << dir << " | xdiff: " << xdiff << ", ydiff: " << ydiff << ", zdiff: " << zdiff << std::endl;
    //std::cout << "p1: " << box.p1 << ", p2: " << box.p2 << std::endl;

    //BoundingBox leftB;
    //BoundingBox rightB;

    
    /*
    Vector3D dia = box.p2 - box.p1;
    switch (dir)
    {
    case 0:
        leftB.p2 = box.p2 - Vector3D(dia.getX() / 2,0,0);
        rightB.p1 = box.p1 + Vector3D(dia.getX() / 2,0,0);
        break;
    case 1:
        leftB.p2 = box.p2 - Vector3D(0,dia.getY() / 2,0);
        rightB.p1 = box.p1 + Vector3D(0,dia.getY() / 2,0);
        break;
    default:
        leftB.p2 = box.p2 - Vector3D(0,0,dia.getZ() / 2);
        rightB.p1 = box.p1 + Vector3D(0,0,dia.getZ() / 2);
        break;
    }
    */
    uint8_t bestdir;
    std::vector<Face3D*> bestleft;
    std::vector<Face3D*> bestright;
    BoundingBox bestleftB;
    BoundingBox bestrightB;
    int optimize = INT_MAX;

    for(int dir = 0; dir < 3; dir++){
        BoundingBox leftB;
        BoundingBox rightB;

        leftB.p1 = box.p1;

        float disectValue = calcDisectValue(dir, faces);
        
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
        }
    }
    
    //std::cout << "total: " << faces.size() << " pivotnr: " << faces.size() / 2 + 1 << " left: " << left.size() << " | right: " << right.size() << std::endl;
    BinaryDisect* newleft = createNode(bestleft, depth, bestleftB); 
    BinaryDisect* newright = createNode(bestright, depth, bestrightB);
    //std::cout << newleft->id << " | " << newright->id << std::endl; 
    return new BinaryNode(newleft,newright,box,bestdir);
}
