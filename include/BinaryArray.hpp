#pragma once
#include "BoundingBox.hpp"
#include "IBinaryDisect.hpp"
#include "vector"

class BinaryArray : IBinaryDisect{
    std::vector<ArrBoundingBox> boxes;

    
};