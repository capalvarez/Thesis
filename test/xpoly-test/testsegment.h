#include <geometry/Point.h>
#include <geometry/Segment.h>
#include "gtest/gtest.h"

class SegmentTest: public ::testing::Test{
protected:
    virtual void SetUp(){
        Point* p1 = new Point(0,0);
        Point* p2 = new Point(1,1);

        segment_points = {*p1,*p2};
        segment = new Segment(0,1);
    }

    std::vector<Point> segment_points;
    Segment* segment;
};

