#ifndef THESIS_POLYGON_H
#define THESIS_POLYGON_H


#include "Point.h"

class Polygon {
private:
    std::vector<int> points;
    double signedArea(std::vector<Point> p)
public:
    double diameter(std::vector<Point> p);
    double area(std::vector<Point> p);
    Point getCentroid(std::vector<Point> p);
};


#endif
