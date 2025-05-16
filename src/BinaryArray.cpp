#include "../include/BinaryArray.hpp"
#include <algorithm>

BinaryArray::BinaryArray(std::vector<Face3D*> faces, int maxDepth, BoundingBox box){
    
}

void BinaryArray::buildArray(size_t pos, u_int8_t dir, BoundingBox box, std::vector<Face3D*> faces){
    std::vector<Face3D*> left;
    std::vector<Face3D*> right;
    BoundingBox leftB;
    BoundingBox rightB;

    std::sort(faces.begin(), faces.end(), [dir](Face3D* a,Face3D* b){return Face3D::smallerEqDir(a,b,dir);});
    float middle = faces.at(faces.size() / 2)->middlePoint().at(dir); 

    leftB.p1 = box.p1;
    leftB.p2 = box.p2;
    leftB.p2.at(dir) = middle;
    rightB.p1 = box.p1;
    rightB.p1.at(dir) = middle;
    rightB.p2 = box.p2;

    for(int i = 0; i < faces.size(); i++){
        //std::cout << "i: " << i << " | " << *faces.at(i) << std::endl;
        bool smaller = false, bigger = false;
        for(Vector3D* p : faces.at(i)->points){
            if(p->at(dir) < middle){
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
    

}