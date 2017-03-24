#ifndef THESIS_SEGMENT_H
#define THESIS_SEGMENT_H

#include <vector>
#include <x-poly/models/basic/Point.h>
#include <x-poly/utilities/xpolyutilities.h>
#include <x-poly/config/XPolyConfig.h>

template <class T>
class Segment {
protected:
    T p1;
    T p2;

    double length(Point p1, Point p2);
    bool intersects(Point p1, Point p2, Point o1, Point o2, Point& inter);
public:
    Segment();
    Segment(T p1, T p2);
    ~Segment();

    T getFirst() const;
    T getSecond() const;

    virtual std::string getString() const = 0;
    bool contains(Point point, Point p1, Point p2);
    bool isVertex(T p);
    virtual bool isBoundary(std::vector<Point> p) = 0;
    double cartesianAngle(Point p1, Point p2);

    bool intersectionInfinite(Point p1, Point p2, Point o1, Point o2, Point &inter);
};

#endif



