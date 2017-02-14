#ifndef THESIS_SEGMENT_H
#define THESIS_SEGMENT_H

#include <vector>
#include <x-poly/models/basic/Point.h>
#include <x-poly/utilities/xpolyutilities.h>


template <class T>
class Segment {
protected:
    T p1;
    T p2;
public:
    Segment();
    Segment(T p1, T p2);
    ~Segment();

    T getFirst() const;
    T getSecond() const;

    virtual std::string getString() const = 0;
    bool contains(Point point, Point p1, Point p2);
    virtual bool isBoundary(std::vector<Point> p) = 0;
};

#endif



