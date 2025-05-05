#include "../include/Point3D.hpp"

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
}
