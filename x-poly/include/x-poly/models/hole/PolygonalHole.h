#ifndef THESIS_POLYGONALHOLE_H
#define THESIS_POLYGONALHOLE_H

#include <vector>
#include <x-poly/models/polygon/Polygon.h>
#include "Hole.h"


class PolygonalHole: public Hole, public Polygon{
private:
    std::vector<Point> points;
public:
    PolygonalHole(std::vector<Point>& p);

    Point getCenter();
};


#endif
