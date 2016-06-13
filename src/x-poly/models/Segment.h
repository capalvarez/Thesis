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

    int getFirst() const;
    int getSecond() const;
    bool operator==(const Segment other) const;

    bool contains(std::vector<Point>& p, Point point);
    Point middlePoint(std::vector<Point> p);
};

#endif



