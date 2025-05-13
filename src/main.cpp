#include <fstream>
#include <iostream>
#include <chrono>
#include "../include/Scene.hpp"

int main()
{
    Scene test;
    std::ifstream file;
    std::string filePath = "models/tommygun.ply";
    file.open(filePath,std::ios::in);
    if(!file.is_open()){
        std::cout << "File not opened" << std::endl;
        return -1;
    }
    test.loadFile(file);
    test.camera = Camera(Vector3D(0.7,0, -3), Vector3D(0,0,1), 1.75, 0.875, 200, 100);
    auto start = std::chrono::high_resolution_clock::now();
    test.drawPicture();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Execution time: " << duration.count() << " seconds." << std::endl;

    return 0;
}
