#ifndef THESIS_RECTANGLE_H
#define THESIS_RECTANGLE_H

#include "models/basic/Point.h"

class Rectangle {
private:
    Point p1;
    Point p2;
public:
    Rectangle(Point p1, Point p2);

    double getWidth();
    double getHeight();
    double xMin();
    double yMin();
};


#endif
