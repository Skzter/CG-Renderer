#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <chrono>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "../include/Scene.hpp"

int main(int argc, char **argv)
{
    std::srand(std::time({}));
    std::ifstream file;
    std::string filePath = "models/big_porsche.ply";
    file.open(filePath,std::ios::in);
    if(!file.is_open()){
        std::cout << "File not opened" << std::endl;
        return -1;
    }

    Scene test(file, 15);
    test.loadGraphics({
        std::string("textures/red.png"),
        std::string("textures/red.png"),
        std::string("textures/red.png"),
        std::string("textures/red.png"),
        std::string("textures/red.png"),
        std::string("textures/red.png"),
    });

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

    //Topdown
    //Vector3D eye = Vector3D(0,300, 0);
    //Vector3D view = Vector3D(0,-280,0);

    Vector3D eye = Vector3D(5,10, -15);
    Vector3D view = Vector3D(-0.3,-0.6,1);

    float vw = 1;

    test.lights = {
        Light(Vector3D(0,20, -10), 100, Color(255,255,255)),
    };

    std::cout << "Preset: ";

    size_t x, y;
    switch (type) 
    {
    case 1:
        std::cout << "1" << std::endl;
        x = 1920;
        y = 1080;
        test.camera = Camera(eye, view, vw, (float)y/(float)x * vw, x, y);
        break;
    case 2:
        std::cout << "2" << std::endl;
        x = 1280;
        y = 720;
        test.camera = Camera(eye, view, vw, (float)y/(float)x * vw, x, y);
        break;
    case 3:
        x = 500;
        y = 250;
        std::cout << "3" << std::endl;
        test.camera = Camera(eye, view, vw, (float)y/(float)x * vw, x, y);
        break;
    case 4:
        x = 10;
        y = 10;
        std::cout << "4" << std::endl;
        test.camera = Camera(eye, view, vw, (float)y/(float)x * vw, x, y);
        break;
    default:
        x = 200;
        y = 80;
        std::cout << "default" << std::endl;
        test.camera = Camera(eye, view, vw, (float)y/(float)x * vw, x, y);
    }
  
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
