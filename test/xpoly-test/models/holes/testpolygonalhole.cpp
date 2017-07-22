#include "testpolygonalhole.h"

TEST_F(PolygonalHoleTest, PointsTest){
    std::vector<Point> expected = {Point(0,0),Point(1,0),Point(1,1),Point(0,1),Point(0.25,0.25),Point(0.75,0.25),
                                   Point(0.75,0.75),Point(0.25,0.75)};

    std::vector<Point> points = square->getRegionPoints();

    EXPECT_EQ(points, expected);
}

TEST_F(PolygonalHoleTest, SegmentsTest){
    std::vector<IndexSegment> expected = {IndexSegment(0,1),IndexSegment(1,2),IndexSegment(2,3),IndexSegment(3,0),IndexSegment(4,5),
                                          IndexSegment(5,6),IndexSegment(6,7),IndexSegment(7,4)};
    std::vector<IndexSegment> segments;
    square->getSegments(segments);

    EXPECT_EQ(segments, expected);
}

