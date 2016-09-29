#include "testcircularhole.h"

TEST_F(CircularHoleTest, PointTest){
    std::vector<Point> expected = {Point(0,0),Point(1,0),Point(1,1),Point(0,1),Point(0.75,0.5),Point(0.5,0.75),
                                   Point(0.25,0.5),Point(0.5,0.25)};
    std::vector<Point> points = square->getRegionPoints();

    EXPECT_EQ(points, expected);
}

TEST_F(CircularHoleTest, SegmentTest){
    std::vector<Segment> expected = {Segment(0,1),Segment(1,2),Segment(2,3),Segment(3,0),Segment(4,5),Segment(5,6),
                                     Segment(6,7),Segment(7,4)};
    std::vector<Segment> segments;
    square->getSegments(segments);

    EXPECT_EQ(segments, expected);
}