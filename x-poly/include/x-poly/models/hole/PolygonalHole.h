#ifndef THESIS_POLYGONALHOLE_H
#define THESIS_POLYGONALHOLE_H

#include <vector>
#include <x-poly/models/polygon/Polygon.h>
#include <x-poly/models/hole/Hole.h>

class PolygonalHole: public Hole, public Polygon{
public:
    PolygonalHole(std::vector<Point>& p);

    void getSegments(std::vector<IndexSegment>& s, int offset);
    Point getCenter();

};

#endif
