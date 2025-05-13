#include <fstream>
#include <iostream>
#include "../include/Scene.hpp"

int main()
{
    Scene test;
    std::ifstream file;
    std::string filePath = "models/triangle.ply";
    file.open(filePath,std::ios::in);
    if(!file.is_open()){
        std::cout << "File not opened" << std::endl;
        return -1;
    }
    test.loadFile(file);
    test.camera = Camera(Vector3D(0,0, -2), Vector3D(0,0,1), 1.5, 1.5, 40, 40);
    test.drawPicture();

    return 0;
}
