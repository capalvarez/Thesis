#ifndef THESIS_REGION_H
#define THESIS_REGION_H

#include <vector>
#include "Segment.h"
#include "Hole.h"

class Region {
private:
    std::vector<Segment> segments;
    std::vector<Hole> holes;

public:
    Region(std::vector<Point> points);
    ~Region();

    std::vector<Segment> getSegments();
    std::vector<Hole> getHoles();
};


#endif
