#include "../include/BinaryDisect.hpp"
#include <cmath>
#include <iostream>

int BinaryDisect::mostFaces = 0;

BinaryNode::BinaryNode(BinaryDisect* left, BinaryDisect* right, BoundingBox box){
    this->left = left;
    this->right = right;
    this->box = box;
    this->empty = left->empty && right->empty;
}

void BinaryNode::dealoc(){
    this->left->dealoc();
    this->right->dealoc();
    delete this;
}

void BinaryLeaf::dealoc(){
    delete this;
}

BinaryNode::~BinaryNode(){
    //std::cout << "Node deleted" << std::endl;
}

BinaryLeaf::~BinaryLeaf(){
    //std::cout << "Leaf deleted" << std::endl;
}

Hitpoint BinaryNode::closestHitpoint(Ray& ray){
    if(this->empty){
        return Hitpoint();
    }

    if(!ray.check(this->box)){
        //std::cout << "missed Box" << std::endl;
        return Hitpoint();
    }

    //std::cout << left->id << " | " << right->id << std::endl;

    Hitpoint h1 = this->left->closestHitpoint(ray);
    Hitpoint h2 = this->right->closestHitpoint(ray);
    return h1.distance < h2.distance ? h1 : h2;
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
    this->empty = faces.size() == 0;
    //if(faces.size() != 0)
    //   std::cout << "Num Faces: " << faces.size() << std::endl;
    if(faces.size() > mostFaces){
        mostFaces = faces.size();
    }
}

BinaryDisect* BinaryDisect::createNode(std::vector<Face3D*> faces, int depth, BoundingBox box){
    if(depth-- <= 0){
        return new BinaryLeaf(faces);
    }
    
    std::vector<Face3D*> left;
    std::vector<Face3D*> right;

    uint8_t dir;
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
    //std::cout << (int)dir << " | xdiff: " << xdiff << ", ydiff: " << ydiff << ", zdiff: " << zdiff << std::endl;
    //std::cout << "p1: " << box.p1 << ", p2: " << box.p2 << std::endl;

    BoundingBox leftB;
    BoundingBox rightB;

    leftB.p1 = box.p1;
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
    rightB.p2 = box.p2;

    for(int i = 0; i < faces.size(); i++){
        //std::cout << "i: " << i << " | " << *faces.at(i) << std::endl;
        bool smaller = false, bigger = false;
        for(Vector3D* p : faces.at(i)->points){
            switch (dir)
            {
            case 0:
                if(p->getX() < leftB.p2.getX()){
                    smaller = true;
                }else{
                    bigger = true;
                }
                break;

            case 1:
                if(p->getY() < leftB.p2.getY()){
                    smaller = true;
                }else{
                    bigger = true;
                }
                break;

            default:
                if(p->getZ() < leftB.p2.getZ()){
                    smaller = true;
                }else{
                    bigger = true;
                }
                break;
            }
            //std::cout << *p << " | " << leftB.p2 << "   bigger: " << bigger << ", smaller: " << smaller << std::endl;
        }
        if(!(smaller || bigger)){
            throw std::runtime_error("neither bigger nor smaller!");
        }
        if(smaller && bigger){
            //std::cout << "auf der Kante: " << *faces.at(i) << " | " << leftB.p2 << std::endl;
        }
        if(smaller){
            left.push_back(faces.at(i));
        }
        if(bigger){
            right.push_back(faces.at(i));
        }
    }
    BinaryDisect* newleft = createNode(left, depth, leftB);
    BinaryDisect* newright = createNode(right, depth, rightB);
    //std::cout << newleft->id << " | " << newright->id << std::endl; 
    return new BinaryNode(newleft,newright,box);
}