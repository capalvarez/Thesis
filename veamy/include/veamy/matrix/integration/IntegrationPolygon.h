#ifndef THESIS_VEMPOLYGON_H
#define THESIS_VEMPOLYGON_H

#include <x-poly/models/polygon/Polygon.h>
#include <x-poly/models/basic/Point.h>
#include <veamy/matrix/integration/IntegrationTriangle.h>
#include <veamy/matrix/integration/IntegrationFunction.h>

typedef double(*func_t)(double, double);

class IntegrationPolygon : public Polygon{
private:
    IntegrationTriangle getEar(std::vector<Point> points, std::vector<int>& pointList);
public:
    IntegrationPolygon(std::vector<int> index, std::vector<Point> points);
    std::vector<IntegrationTriangle> triangulate(std::vector<IntegrationTriangle>& triangles, std::vector<Point>& points);

    double integrate(IntegrationFunction* f, std::vector<Point> points);
};

#endif