#ifndef THESIS_ROSETTEGROUPGENERATOR_H
#define THESIS_ROSETTEGROUPGENERATOR_H

#include <x-poly/models/basic/Point.h>
#include <vector>
#include <x-poly/utilities/utilities.h>
#include <x-poly/models/Region.h>

class RosetteGroupGenerator{
private:
    Point center;
    std::vector<Point> points;

    double innerRadius;
    double outerRadius;

    double angle;

    void cleanPoints(Region region);
    void generatePoint(double angle, double radius);
public:
    RosetteGroupGenerator(Point c, double outer, double angle);
    std::vector<Point> getPoints(double initAngle, Region region);
};


#endif 
