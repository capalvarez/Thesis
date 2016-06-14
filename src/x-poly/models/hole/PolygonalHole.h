#ifndef THESIS_POLYGONALHOLE_H
#define THESIS_POLYGONALHOLE_H

#include <vector>
#include "models/hole/Hole.h"
#include "models/polygon/Polygon.h"
#include "models/basic/Segment.h"
#include <utilities/utilities.cpp>

class PolygonalHole: public Hole, public Polygon{
private:
    std::vector<Point> points;
public:
    PolygonalHole(std::vector<Point>& p);

    Point getCenter();
};


#endif
