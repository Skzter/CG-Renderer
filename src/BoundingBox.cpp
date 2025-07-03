#include "../include/BoundingBox.hpp"
#include <cstdint>

bool BoundingBox::contains(Vector3D& vec){
	for(uint8_t dir = 0; dir < 3; dir++){
		if(vec.at(dir) < this->p1.at(dir) || vec.at(dir) > this->p2.at(dir)){
			return false;
		}
	}
	return true;
}

void BoundingBox::expandToInclude(BoundingBox other){
    for(uint8_t dim = 0; dim < 3; dim++){
        if(this->p1.at(dim) > other.p1.at(dim)){
            this->p1.at(dim) = other.p1.at(dim);
        }
        if(this->p2.at(dim) < other.p2.at(dim)){
            this->p2.at(dim) = other.p2.at(dim);
        }
    }
}