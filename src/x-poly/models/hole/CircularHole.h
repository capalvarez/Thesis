#ifndef THESIS_CIRCULARHOLE_H
#define THESIS_CIRCULARHOLE_H

#include <vector>
#include "models/basic/Point.h"
#include "Hole.h"
#include "models/basic/Segment.h"
#include "models/polygon/Circle.h"
#include <utilities/utilities.h>

class CircularHole: public Hole, public Circle {
private:
    std::vector<Point> discrete_points;
public:
    CircularHole(Point p, double r);

    Point getCenter();
    void getSegments(std::vector<Segment> segments);
};


#endif