#ifndef THESIS_POLYGONALHOLE_H
#define THESIS_POLYGONALHOLE_H

#include <vector>
#include "Hole.h"
#include "Polygon.h"
#include "Segment.h"

class PolygonalHole: public Hole, public Polygon {
private:
    std::vector<Point> points;
public:
    PolygonalHole(std::vector<Point> p);
    ~PolygonalHole();

    Point getCenter();
    virtual std::vector<Segment*> getSegments();
};


#endif //THESIS_POLYGONALHOLE_H
