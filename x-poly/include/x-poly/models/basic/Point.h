#ifndef THESIS_POINT_H
#define THESIS_POINT_H

#include <string>
#include "Point3D.h"
#include <math.h>
#include <cmath>


class Point {
private:
    double x;
    double y;
    bool isBoundaryPoint = false;
public:
    Point(double x, double y);
    Point();

    double getX() const;
    double getY() const;

    double squareNorm();
    std::string getString();
    bool operator==(const Point& other) const;
    Point operator-(const Point& other);
    Vector operator-(Point& other);

    Point3D get3DPoint();
    bool isInBoundary();
    void setBoundary();

    void setX(double newX);
    void setY(double newY);
};

#endif