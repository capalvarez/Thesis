#ifndef THESIS_TRIANGLE_H
#define THESIS_TRIANGLE_H

#include "models/polygon/Polygon.h"

class Triangle : public Polygon{
public:
    Triangle(std::vector<int> points, std::vector<Point>& p);
    Point getCircumcenter(std::vector<Point>& p);
};

#endif


