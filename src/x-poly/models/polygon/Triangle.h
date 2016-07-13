#ifndef THESIS_TRIANGLE_H
#define THESIS_TRIANGLE_H

#include <x-poly/models/polygon/Polygon.h>

class Triangle : public Polygon{
private:
    Point circumcenter;
    Point calculateCircumcenter(std::vector<Point>& p);
public:
    Triangle(std::vector<int> points, std::vector<Point>& p);
    Point getCircumcenter();
};

#endif


