#ifndef THESIS_POLYGONALHOLE_H
#define THESIS_POLYGONALHOLE_H

#include <vector>
#include "Hole.h"
#include "Polygon.h"
#include "Segment.h"

class PolygonalHole: public Hole{
private:
    std::vector<Point> points;
public:
    PolygonalHole(std::vector<Point> p);

    Point getCenter();
    void getSegments(std::vector<Segment> segments);
};


#endif
