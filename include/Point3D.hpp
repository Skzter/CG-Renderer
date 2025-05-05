#pragma once

class Point3D
{
private:
    int X;
    int Y;
    int Z;

public:
    Point3D();
    void setPoint(int x, int y, int z);
    Point3D getPoint(Point3D point);
    void printPoint();
    void addPoint(Point3D point);
};
