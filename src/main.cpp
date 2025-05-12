#include <fstream>
#include <iostream>
#include "../include/Scene.hpp"

int main()
{
    Scene test;
    std::ifstream file;
    file.open("test.ply",std::ios::in);
    if(!file.is_open()){
        std::cout << "File not opened" << std::endl;
    }
    test.loadFile(file);
    test.camera = Camera(Vector3D(0,0, -10), Vector3D(0,0,1), 10.0, 10.0, 100, 100);
    test.drawPicture();

    //Vector3D vec1 = Vector3D(0,1,1), vec2 = Vector3D(0,1,0);
    //std::cout << Vector3D::dot(vec1, vec2) << std::endl;
    /*
    Point3D p;
    p.setPoint(2,3,5);
    p.printPoint();

    Point3D p2;
    p2.setPoint(1,1,1);
    p2.printPoint();

    p2.addPoint(p);
    p2.printPoint();

    Point3D p1 = Point3D(7,8,9);
    p1.printPoint();

    Point3D p3 = p + p2;
    p3.printPoint();

    p3 = p3 + p3;
    p3.printPoint();
    std::cout << p3 << std::endl;
    */

    /*
    SDL_Window* window;
    SDL_Renderer* renderer;
    window = SDL_CreateWindow("Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    bool running = true;

    while(running)
    {
	if(SDL_QuitRequested()){ running = false; break; }
    }

    */
    return 0;
}
