#include "Polygon.h"

class Triangle : public Polygon{
public:
    Triangle(std::vector<int> points, std::vector<Point> p);
    Point getCircumcenter(std::vector<Point> p);
};



