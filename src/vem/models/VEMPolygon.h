#ifndef THESIS_VEMPOLYGON_H
#define THESIS_VEMPOLYGON_H

#include <x-poly/models/polygon/Polygon.h>
#include <x-poly/models/basic/Point.h>
#include "VEMTriangle.h"

typedef double(*func_t)(double, double);

class VEMPolygon : public Polygon{
public:
    VEMPolygon(std::vector<int> index, std::vector<Point> points);
    std::vector<VEMTriangle> triangulate(std::vector<Point> points);

    double getAverage(func_t f, std::vector<Point> points);
};


#endif //THESIS_VEMPOLYGON_H
