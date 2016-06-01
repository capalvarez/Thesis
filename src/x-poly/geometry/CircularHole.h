#ifndef THESIS_CIRCULARHOLE_H
#define THESIS_CIRCULARHOLE_H

#include <vector>
#include "Point.h"
#include "Hole.h"
#include "Segment.h"

class CircularHole: public Hole {
private:
    Point center;
    double radius;
public:
    CircularHole(Point p, double r);
    ~CircularHole();

    Point getCenter();
    std::vector<Segment*> getSegments();
};


#endif //THESIS_CIRCULARHOLE_H
