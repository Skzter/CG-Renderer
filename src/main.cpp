#include "../include/Point3D.hpp"
#include <iostream>

int main()
{
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
}
