#ifndef THESIS_POINT_H
#define THESIS_POINT_H

#include <string>
#include "Point3D.h"
#include <math.h>
#include <cmath>
#include <x-poly/utilities/utilities.h>

class Point {
private:
    double x;
    double y;
public:
    Point(double x, double y);
    Point();

    double getX() const;
    double getY() const;

    double squareNorm();
    std::string getString();
    bool operator==(const Point& other) const;
    Vector operator-(Point& other);

    Point3D get3DPoint();
};

#endif