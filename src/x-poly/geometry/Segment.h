#ifndef THESIS_SEGMENT_H
#define THESIS_SEGMENT_H

#include <vector>
#include "Point.h"

class Segment {
private:
    int p1;
    int p2;
public:
    Segment(int p1, int p2);
    ~Segment();

    int getFirst();
    int getSecond();
    bool operator==(Segment& other);

    bool contains(std::vector<Point> p, Point point);
    Point middlePoint(std::vector<Point> p);
};

#endif



