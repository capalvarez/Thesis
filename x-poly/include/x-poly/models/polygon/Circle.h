#ifndef THESIS_CIRCLE_H
#define THESIS_CIRCLE_H

#include <vector>
#include <x-poly/models/basic/Point.h>
#include <cstdlib>
#include <cmath>
#include <x-poly/utilities/geometryFunctions.h>
#include <x-poly/utilities/xpolyutilities.h>

class Circle {
protected:
    double radius;
    Point center;
public:
    Circle(double r, Point c);
    std::vector<Point> discretizeCircle(int grade);
};


#endif
