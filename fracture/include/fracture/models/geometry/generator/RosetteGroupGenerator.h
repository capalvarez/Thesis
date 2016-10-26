#ifndef THESIS_ROSETTEGROUPGENERATOR_H
#define THESIS_ROSETTEGROUPGENERATOR_H

#include <x-poly/models/basic/Point.h>
#include <vector>
#include <x-poly/utilities/utilities.h>

class RosetteGroupGenerator{
private:
    Point center;
    std::vector<Point> points;

    double innerRadius;
    double outerRadius;

    double angle;
public:
    RosetteGroupGenerator(Point c, double inner, double outer, double angle);
    std::vector<Point> getPoints(double initAngle);
};


#endif 
