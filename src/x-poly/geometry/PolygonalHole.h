#ifndef THESIS_POLYGONALHOLE_H
#define THESIS_POLYGONALHOLE_H

#include <vector>
#include "Hole.h"
#include "Polygon.h"
#include "Segment.h"
#include <utilities/utilities.cpp>

class PolygonalHole: public Hole, public Polygon{
private:
    std::vector<Point> points;
public:
    PolygonalHole(std::vector<Point>& p);

    Point getCenter();
};


#endif
