#ifndef THESIS_SEGMENT_H
#define THESIS_SEGMENT_H

#include <vector>
#include <x-poly/models/basic/Point.h>

template <class T>
class Segment {
private:
    T p1;
    T p2;
public:
    Segment();
    Segment(T p1, T p2);
    ~Segment();

    T getFirst() const;
    T getSecond() const;
    bool operator==(const Segment<T> other) const;
    std::string getString();

    bool contains(std::vector<Point>& p, Point point);
    bool contains(std::vector<Point> p, Segment<int> s);
    Point middlePoint(std::vector<Point> p);
};

#endif



