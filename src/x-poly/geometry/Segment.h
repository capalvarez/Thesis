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
    bool collinear(std::vector<Point> points, Point p);
    bool operator==(Segment& other);
};


#endif //THESIS_SEGMENT_H
