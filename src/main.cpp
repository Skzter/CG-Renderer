#include <fstream>
#include <iostream>
#include <chrono>
#include "../include/Scene.hpp"
#include "../include/Quickselect.hpp"

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
    std::string filePath = "models/tommygun.ply";
    file.open(filePath,std::ios::in);
    if(!file.is_open()){
        std::cout << "File not opened" << std::endl;
        return -1;
    }
    test.loadFile(file);

    test.camera = Camera(Vector3D(0.6,0, -5), Vector3D(0,0,1), 1.0, 0.4, 2000, 800);
    BoundingBox box;
    box.p1 = Vector3D(-7.0,-3.0,-3.0);
    box.p2 = Vector3D(7,3.0,3.0);
    
    /*
    Vector3D v1 = Vector3D(-1,0,1);
    Vector3D v2 = Vector3D(1,-1,0);
    Vector3D v3 = Vector3D(0,1,-1);
    Face3D f = Face3D({&v1,&v2,&v3},Texture());
    std::cout << f.maxW(0) << " " << f.minW(1) << std::endl;
    */

    auto start = std::chrono::high_resolution_clock::now();
    //test.drawPicture();
    test.testoptimized(box,18);
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
