#ifndef THESIS_ROSETTEGROUPGENERATOR_H
#define THESIS_ROSETTEGROUPGENERATOR_H

#include <x-poly/models/basic/Point.h>

class RosetteGroupGenerator{
private:
    Point center;
    std::vector<Point> points;

    double innerRadius;
    double outerRadius;

    double angle;
public:
    // TODO: Ask the user this parameters!
    RosetteGroupGenerator(Point c, double inner, double outer, double angle);
    std::vector<Point> getPoints();
};


#endif 
