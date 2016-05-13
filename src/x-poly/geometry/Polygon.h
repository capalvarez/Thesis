#ifndef THESIS_POLYGON_H
#define THESIS_POLYGON_H


#include "Point.h"

class Polygon {
private:

public:
    double diameter();
    double area();
    Point getCircumcircle();
    Point getCentroid();

};


#endif
