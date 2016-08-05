#ifndef THESIS_CIRCULARHOLE_H
#define THESIS_CIRCULARHOLE_H

#include <vector>
#include <x-poly/models/basic/Point.h>
#include "Hole.h"
#include <x-poly/models/basic/Segment.h>
#include <x-poly/utilities/utilities.h>
#include <x-poly/models/polygon/Circle.h>

class CircularHole: public Hole, public Circle {
public:
    CircularHole(Point p, double r, int grade);

    Point getCenter();
    void getSegments(std::vector<Segment>& segments, int offset);
    std::vector<Point> getPoints();
};


#endif
