#ifndef THESIS_ROSETTEGROUPGENERATOR_H
#define THESIS_ROSETTEGROUPGENERATOR_H

#include <x-poly/models/basic/Point.h>
#include <vector>
#include <x-poly/utilities/xpolyutilities.h>
#include <x-poly/models/Region.h>
#include <fracture/geometry/BreakableMesh.h>

class QPEGenerator{
private:
    Point center;
    std::vector<Point> points;
    std::vector<Polygon> elements;
    std::vector<int> borderPoints;

    double angle;
    double innerRadius;
    double outerRadius;

    int generatePoint(double angle, double radius);
public:
    QPEGenerator(Point c, double angle, double radius);
    void generateGroup(double initAngle);
    std::vector<Point> getPoints();
    std::vector<int> getBorderPoints();
    std::vector<Polygon> getElements();
};


#endif 
