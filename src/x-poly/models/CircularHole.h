#ifndef THESIS_CIRCULARHOLE_H
#define THESIS_CIRCULARHOLE_H

#include <vector>
#include "Point.h"
#include "Hole.h"
#include "Segment.h"
#include "Circle.h"
#include <utilities/utilities.cpp>

class CircularHole: public Hole, public Circle {
private:
    std::vector<Point> discrete_points;
public:
    CircularHole(Point p, double r);

    Point getCenter();
    void getSegments(std::vector<Segment> segments);
};


#endif
