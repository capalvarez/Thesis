#ifndef THESIS_POLYGONALHOLE_H
#define THESIS_POLYGONALHOLE_H

#include <vector>
#include <x-poly/models/hole/Hole.h>
#include <x-poly/models/polygon/Polygon.h>
#include <x-poly/models/basic/Segment.h>
#include <x-poly/utilities/utilities.h>

class PolygonalHole: public Hole, public Polygon{
public:
    PolygonalHole(std::vector<Point>& p);

    void getSegments(std::vector<Segment>& s, int offset);
    Point getCenter();
    std::vector<Point> getPoints();
};

#endif
