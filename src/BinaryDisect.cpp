#include "../include/BinaryDisect.hpp"
#include <cmath>
#include <iostream>

std::vector<BinaryDisect> BinaryDisect::all = std::vector<BinaryDisect>();

BinaryDisect::BinaryDisect(std::vector<Face3D*> faces, int depth, BoundingBox box){
    if(depth-- <= 0){
        this->left = nullptr;
        this->right = nullptr;
        this->faces = faces;
        return;
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
    std::cout << (int)dir << " | xdiff: " << xdiff << ", ydiff: " << ydiff << ", zdiff: " << zdiff << std::endl;
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
        bool smaller = true, bigger = true;
        for(Vector3D* p : faces.at(i)->points){
            switch (dir)
            {
            case 0:
                if(p->getX() < leftB.p2.getX()){
                    bigger = false;
                }else{
                    smaller = false;
                }
                break;

            case 1:
                if(p->getY() < leftB.p2.getY()){
                    bigger = false;
                }else{
                    smaller = false;
                }
                break;

            default:
                if(p->getZ() < leftB.p2.getZ()){
                    bigger = false;
                }else{
                    smaller = false;
                }
                break;
            }
            //std::cout << *p << " | " << leftB.p2 << "   bigger: " << bigger << ", smaller: " << smaller << std::endl;
        }
        if(!(smaller || bigger)){
               // std::cout << "auf der Kante: " << *faces.at(i) << " | " << leftB.p2 << std::endl;
        }
        if(smaller && bigger){
            throw std::runtime_error("bigger and smaller!");
        }
        if(smaller){
            left.push_back(faces.at(i));
            faces.erase(faces.begin() + i);
        }
        if(bigger){
            right.push_back(faces.at(i));
            faces.erase(faces.begin() + i);
        }
    }
    std::cout << faces.size() << std::endl;

    this->faces = faces;
    BinaryDisect::all.push_back(BinaryDisect(left, depth, leftB));
    this->left = &BinaryDisect::all.back();
    BinaryDisect::all.push_back(BinaryDisect(right, depth, rightB));
    this->right = &BinaryDisect::all.back();
}