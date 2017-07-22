#ifndef THESIS_QUADRATUREPOLYGON_H
#define THESIS_QUADRATUREPOLYGON_H

#include <x-poly/models/polygon/Polygon.h>
#include <vector>
#include <veamy/physics/BodyForce.h>

class QuadraturePolygon {
private:
    Polygon polygon;
public:
    QuadraturePolygon(Polygon p);
    double integrate(BodyForce* f, std::vector<Point> points);
};


#endif
