#include <fstream>
#include <iostream>
#include "../include/Scene.hpp"

int main()
{
    Scene test;
    std::ifstream file;
    std::string filePath = "models/big_porsche.ply";
    file.open(filePath,std::ios::in);
    if(!file.is_open()){
        std::cout << "File not opened" << std::endl;
        return -1;
    }
    test.loadFile(file);
    test.camera = Camera(Vector3D(0,0, -10), Vector3D(0,0,1), 2.0, 2.0, 400, 400);
    //test.drawPicture();

    BoundingBox box;
	box.p1 = Vector3D(-6.0,-2.0,-3.0);
	box.p2 = Vector3D(6,2.0,3.0);

    test.testoptimized(box,15);

    /*BoundingBox testb;
    testb.p1 = Vector3D(-1,-1,-1);
    testb.p2 = Vector3D(1,1,1);
    Ray testr = Ray(Vector3D(1.1,0,-2),Vector3D(-0.1,0,1));
    std::cout << testr.check(testb) << std::endl;*/
    return 0;
}
