#ifndef THESIS_ROSETTEGROUPGENERATOR_H
#define THESIS_ROSETTEGROUPGENERATOR_H

#include <x-poly/models/basic/Point.h>
#include <vector>
#include <x-poly/utilities/xpolyutilities.h>
#include <x-poly/models/Region.h>
#include <fracture/geometry/BreakableMesh.h>

class RosetteGroupGenerator{
private:
    Point center;
    std::vector<Point> points;
    double angle;
    double innerRadius;
    double outerRadius;

    void generatePoint(double angle, double radius);
public:
    RosetteGroupGenerator(Point c, double angle, double radius);
    std::vector<Point> getPoints(double initAngle);
};


#endif 
