#ifndef THESIS_SEGMENT_H
#define THESIS_SEGMENT_H

#include <vector>
#include <x-poly/models/basic/Point.h>
#include <x-poly/utilities/utilities.h>

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

    double length();
    bool operator==(const Segment<T> other) const;
    std::string getString();

    bool contains(std::vector<Point>& p, Point point);
    bool contains(std::vector<Point> p, Segment<int> s);
    Point middlePoint(std::vector<Point> p);
    bool isBoundary(std::vector<Point> p);
    bool intersection(std::vector<Point> points, Segment<Point> other, Point &inter);
    void orderCCW(std::vector<Point> points, Point center);
    double cartesianAngle(std::vector<Point> p);
};

#endif



