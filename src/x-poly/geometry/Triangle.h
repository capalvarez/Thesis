#include "Polygon.h"

class Triangle : public Polygon{
public:
    Triangle(std::vector<int> points);
    Point getCircumcenter(std::vector<Point> p);
};



