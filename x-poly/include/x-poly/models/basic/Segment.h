#ifndef THESIS_SEGMENT_H
#define THESIS_SEGMENT_H

#include <vector>
#include <x-poly/models/basic/Point.h>

class Segment {
private:
    int p1;
    int p2;
public:
    Segment(int p1, int p2);
    Segment();
    Segment(const Segment& other);

    int getFirst() const;
    int getSecond() const;
    bool operator==(const Segment other) const;
    std::string getString();

    bool contains(std::vector<Point>& p, Point point);
    Point middlePoint(std::vector<Point> p);
};

#endif



