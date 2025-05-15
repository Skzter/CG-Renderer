#include "../include/BinaryDisect.hpp"
#include <cmath>
#include <iostream>
#include "../include/Quickselect.hpp"
#include <algorithm>

int BinaryDisect::mostFaces = 0;
int BinaryDisect::sumFaces = 0;
int BinaryDisect::cntLeafs = 0;

Hitpoint BinaryEmpty::closestHitpoint(Ray&){
    return Hitpoint();
}

void BinaryDisect::dealoc(){
    //std::cout << "deleting smth else" << std::endl;
     delete this;
}

BinaryNode::BinaryNode(BinaryDisect* left, BinaryDisect* right, BoundingBox box){
    this->left = left;
    this->right = right;
    this->box = box;
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

    //std::cout << left->id << " | " << right->id << std::endl;

    Hitpoint h1 = this->left->closestHitpoint(ray);
    Hitpoint h2 = this->right->closestHitpoint(ray);
    
    if(h1.distance < h2.distance){
        //delete h2;
        return h1;
    }else{
        //delete h1;
        return h2;
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

    if(faces.size() == 0){
        return new BinaryEmpty();
    }
    if(depth-- <= 0 || faces.size() < 5){
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
    std::vector<Face3D*> bestleft;
    std::vector<Face3D*> bestright;
    BoundingBox bestleftB;
    BoundingBox bestrightB;
    int optimize = INT_MAX;

    for(int dir = 0; dir < 3; dir++){
        std::vector<Face3D*> left;
        std::vector<Face3D*> right;
        BoundingBox leftB;
        BoundingBox rightB;

        leftB.p1 = box.p1;

        //Vector3D middlePoint = Quickselect::kthSmallestDir(faces, 0, faces.size()-1, faces.size() / 2 + 1, dir);
        std::sort(faces.begin(), faces.end(), [dir](Face3D* a,Face3D* b){return Face3D::smallerEqDir(a,b,dir);});
        Vector3D optimalPoint = faces.at(faces.size() / 2)->middlePoint(); 
        Vector3D middlePoint = (box.p1 + box.p2) * 0.5; 
        Vector3D weighted = optimalPoint * 0.3 + middlePoint * 0.7;

        leftB.p2 = box.p2;
        leftB.p2.at(dir) = weighted.at(dir);
        rightB.p1 = box.p1;
        rightB.p1.at(dir) = weighted.at(dir);
        rightB.p2 = box.p2;

        //std::cout << ", box p1: " << box.p1 << ", box p2: " << box.p2 << ": " << middlePoint << std::endl; 

        for(int i = 0; i < faces.size(); i++){
            //std::cout << "i: " << i << " | " << *faces.at(i) << std::endl;
            bool smaller = false, bigger = false;
            for(Vector3D* p : faces.at(i)->points){
                if(p->at(dir) < weighted.at(dir)){
                    smaller = true;
                }else{
                    bigger = true;
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
        int val = left.size() + right.size();
        if(val < optimize){
            bestleft = left;
            bestright = right;
            bestleftB = leftB;
            bestrightB = rightB;
            optimize = val;
        }
    }

    
    //std::cout << "total: " << faces.size() << " pivotnr: " << faces.size() / 2 + 1 << " left: " << left.size() << " | right: " << right.size() << std::endl;
    BinaryDisect* newleft = createNode(bestleft, depth, bestleftB); 
    BinaryDisect* newright = createNode(bestright, depth, bestrightB);
    //std::cout << newleft->id << " | " << newright->id << std::endl; 
    return new BinaryNode(newleft,newright,box);
}