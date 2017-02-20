#include <x-poly/models/basic/Point.h>
#include <x-poly/models/basic/Segment.h>
#include <gtest/gtest.h>
#include <x-poly/models/basic/IndexSegment.h>

class SegmentTest: public ::testing::Test{
protected:
    virtual void SetUp(){
        segment_points = {Point(0,0), Point(1,1), Point(-1,1), Point(-1,-1), Point(1,-1)};
        segment = new IndexSegment(0,1);
    }

    std::vector<Point> segment_points;
    IndexSegment* segment;
};

