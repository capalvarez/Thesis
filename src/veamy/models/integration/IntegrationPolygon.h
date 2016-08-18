#ifndef THESIS_VEMPOLYGON_H
#define THESIS_VEMPOLYGON_H

#include <x-poly/models/polygon/Polygon.h>
#include <x-poly/models/basic/Point.h>
#include "IntegrationTriangle.h"

typedef double(*func_t)(double, double);

class IntegrationPolygon : public Polygon{
private:
    IntegrationTriangle getEar(std::vector<Point> points, std::vector<int>& pointList);
public:
    IntegrationPolygon(std::vector<int> index, std::vector<Point> points);
    std::vector<IntegrationTriangle> triangulate(std::vector<IntegrationTriangle>& triangles, std::vector<Point>& points);

    double getAverage(func_t f, std::vector<Point> points);
};

#endif