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
    test.camera = Camera(Vector3D(-1,2, -10), Vector3D(0,0,1), 1.0, 1.0, 100, 100);
    //test.drawPicture();
    test.testoptimized();

    return 0;
}
