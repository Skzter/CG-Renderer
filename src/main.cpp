#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <chrono>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include "../include/Scene.hpp"

int main(int argc, char **argv)
{
    std::srand(std::time({}));
    Scene test;
    std::ifstream file;
    std::string filePath = "models/big_dodge.ply";
    file.open(filePath,std::ios::in);
    if(!file.is_open()){
        std::cout << "File not opened" << std::endl;
        return -1;
    }

    test.loadFile(file,12);

    int type;
    bool safe;
    try{
        type = std::stoi(argv[1]);
    }catch(std::logic_error){
        type = 10;
    }

    try{
        safe = std::stoi(argv[2]);
    }catch(std::logic_error){
        safe = false;
    }

    std::cout << "Preset: ";
    switch (type) 
    {
    case 1:
        std::cout << "1" << std::endl;
        test.camera = Camera(Vector3D(0,0, -20), Vector3D(0,0,1), 1.0, 0.5625, 1920, 1080);
        break;
    case 2:
        std::cout << "2" << std::endl;
        test.camera = Camera(Vector3D(0,0, -20), Vector3D(0,0,1), 1.0, 0.5625, 1280, 720);
        break;
    case 3:
        std::cout << "3" << std::endl;
        test.camera = Camera(Vector3D(0,0, -20), Vector3D(0,0,1), 1.0, 1.0, 1000, 1000);
        break;
    case 4:
        std::cout << "4" << std::endl;
        test.camera = Camera(Vector3D(0,0, -20), Vector3D(0,0,1), 1.0, 1.0, 10, 10);
        break;
    default:
        std::cout << "default" << std::endl;
        test.camera = Camera(Vector3D(0,0, -20), Vector3D(0,0,1), 1.0, 0.4, 200, 80); 
    }

    BoundingBox box;
    box.p1 = Vector3D(-7.0,-3.0,-3.0);
    box.p2 = Vector3D(7,3.0,3.0);


  
    tp start = std::chrono::high_resolution_clock::now();
    test.testoptimized(12, start);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    auto mins = std::chrono::duration_cast<std::chrono::minutes>(duration);
    double secs = (duration - mins).count();
    std::cout << "\nExecution time: " << mins.count() << "mins " << secs << "secs." << std::endl;

    if(safe){
        std::cout << "saving to results" << std::endl;
        std::ostringstream oss;
        filePath = filePath.substr(7, filePath.length()-11);
        oss << filePath << "-" << std::fixed << std::setprecision(3) << mins.count() << "m" << secs << "s-" << test.camera.width_pixels << "x" << test.camera.height_pixels << ".png";
        std::filesystem::rename("resultate/output_opt.png", "resultate/" + oss.str());
    }
    
    return 0;
}
