#ifndef THESIS_REGION_H
#define THESIS_REGION_H

#include <vector>
#include "Segment.h"
#include "Hole.h"
#include "Polygon.h"
#include <algorithm>
#include <utilities/utilities.cpp>

class Region: public Polygon {
private:
    std::vector<Hole*> holes;
    std::vector<Point> points;
public:
    Region(std::vector<Point> points);
    ~Region();

    std::vector<Hole*> getHoles();
    void addHole(Hole* h);
};

#endif
