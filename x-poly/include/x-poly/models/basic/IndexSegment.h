#ifndef THESIS_INDEXSEGMENT_H
#define THESIS_INDEXSEGMENT_H

#include <x-poly/models/basic/Segment.h>
#include <x-poly/models/basic/PointSegment.h>


class IndexSegment: public Segment<int>{
public:
    IndexSegment();
    IndexSegment(int i1, int i2);

    bool isBoundary(std::vector<Point> p);
    bool contains(std::vector<Point>& p, Point point);
    bool contains(std::vector<Point> p, IndexSegment s);
    Point middlePoint(std::vector<Point> p);
    double cartesianAngle(std::vector<Point> p);
    bool intersection(std::vector<Point> points, PointSegment other, Point &inter);
    bool intersection(std::vector<Point> points, IndexSegment other, Point &inter);
    void orderCCW(std::vector<Point> points, Point center);
    bool isCCW(std::vector<Point> points, Point center);
    std::string getString() const;
    bool operator==(const IndexSegment& other) const;
    bool operator<(const IndexSegment& other) const;
    double length(std::vector<Point> points);
};


#endif 
