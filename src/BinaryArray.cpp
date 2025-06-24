#include "../include/BinaryArray.hpp"
#include <cmath>
#include <vector>

BinaryArray::BinaryArray(std::vector<Face3D*> faces, int maxDepth, BoundingBox box){
    this->faces = (Face3D**)malloc(sizeof(Face3D*) * std::pow(2, maxDepth));
    this->disects = (float*)malloc(sizeof(float) * std::pow(2, maxDepth));
}

void BinaryArray::calcFace(int pos, int dir){

}

void BinaryArray::dealoc(){
    free(this->faces);
    free(this->disects);
}