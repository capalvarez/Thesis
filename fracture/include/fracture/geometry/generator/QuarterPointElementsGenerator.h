#ifndef THESIS_ROSETTEGROUPGENERATOR_H
#define THESIS_ROSETTEGROUPGENERATOR_H

#include <x-poly/models/basic/Point.h>
#include <vector>
#include <x-poly/utilities/xpolyutilities.h>
#include <x-poly/models/Region.h>
#include <fracture/geometry/BreakableMesh.h>

class QuarterPointElementsGenerator{
private:
    Point center;
    std::vector<Point> points;
    std::vector<Polygon> elements;
    std::vector<Point> borderPoints;

    double angle;
    double innerRadius;
    double outerRadius;

    int generatePoint(double angle, double radius);
public:
    QuarterPointElementsGenerator(Point c, double angle, double radius);
    void generateGroup(double initAngle);
    std::vector<Point> getPoints();
    std::vector<Point> getBorderPoints();
};


#endif 
