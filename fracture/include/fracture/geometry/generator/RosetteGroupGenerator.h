#ifndef THESIS_ROSETTEGROUPGENERATOR_H
#define THESIS_ROSETTEGROUPGENERATOR_H

#include <x-poly/models/basic/Point.h>
#include <vector>
#include <x-poly/utilities/utilities.h>
#include <x-poly/models/Region.h>
#include <fracture/geometry/BreakableMesh.h>

class RosetteGroupGenerator{
private:
    Point center;
    std::vector<Point> points;

    std::set<int> changedPolygons;
    int currentContainer;
    Polygon current;

    double innerRadius;
    double outerRadius;
    double angle;

    void generatePoint(double angle, double radius, BreakableMesh mesh);
public:
    RosetteGroupGenerator(Point c, double outer, double angle, int center_container,
                              Polygon container);
    std::vector<Point> getPoints(double initAngle, BreakableMesh mesh);
    std::vector<Polygon> getChangedPolygons(BreakableMesh mesh);
};


#endif 
