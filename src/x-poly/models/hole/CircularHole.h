#ifndef THESIS_CIRCULARHOLE_H
#define THESIS_CIRCULARHOLE_H

#include <vector>
#include <x-poly/models/basic/Point.h>
#include "Hole.h"
#include <x-poly/models/basic/Segment.h>
#include <x-poly/models/polygon/Circle.h>
#include <x-poly/utilities/utilities.h>

class CircularHole: public Hole, public Circle {
private:
    std::vector<Point> discrete_points;
public:
    CircularHole(Point p, double r);

    Point getCenter();
    void getSegments(std::vector<Segment<int>> segments);
};


#endif
