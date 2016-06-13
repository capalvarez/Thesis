#ifndef THESIS_CIRCLE_H
#define THESIS_CIRCLE_H

#include <vector>
#include "Point.h"
#include <cstdlib>
#include <cmath>
#include <utilities/geometryFunctions.h>

class Circle {
protected:
    double radius;
    Point center;
public:
    Circle(double r, Point c);
    std::vector<Point> discretizeCircle(int grade);
};


#endif
