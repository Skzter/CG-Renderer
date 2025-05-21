#include <fstream>
#include <iostream>
#include <chrono>
#include "../include/Scene.hpp"

int main()
{
    Scene test;
    /*
    Hitpoint defHP = Hitpoint();
    Hitpoint anHP;
    
    std::cout << "defHP - Dist: " << defHP.distance << " Face: " << defHP.face << " Pos: " << defHP.position << std::endl;
    std::cout << "anHP - Dist: " << anHP.distance << " Face: " << anHP.face << " Pos: " << anHP.position << std::endl;
    */
    std::ifstream file;
    std::string filePath = "models/big_porsche.ply";
    file.open(filePath,std::ios::in);
    if(!file.is_open()){
        std::cout << "File not opened" << std::endl;
        return -1;
    }
    test.loadFile(file);

    test.camera = Camera(Vector3D(0,0, -20), Vector3D(0,0,1), 1.0, 0.5625, 480, 270);
    BoundingBox box;
    box.p1 = Vector3D(-7.0,-3.0,-3.0);
    box.p2 = Vector3D(7,3.0,3.0);

  
    auto start = std::chrono::high_resolution_clock::now();
    //test.drawPicture();
    test.testoptimized(box,15);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    auto mins = std::chrono::duration_cast<std::chrono::minutes>(duration);
    double secs = (duration - mins).count();
    std::cout << "Execution time: " << mins.count() << "mins " << secs << "secs." << std::endl;
    /*BoundingBox testb;
    testb.p1 = Vector3D(-1,-1,-1);
    testb.p2 = Vector3D(1,1,1);
    Ray testr = Ray(Vector3D(1.1,0,-2),Vector3D(-0.1,0,1));
    std::cout << testr.check(testb) << std::endl;*/
    return 0;
}
