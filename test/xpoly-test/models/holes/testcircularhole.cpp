#include "testcircularhole.h"

TEST_F(CircularHoleTest, PointTest){
    XPolyConfig::instance()->setDiscretizationGrade(4);

    std::vector<Point> expected = {Point(0,0),Point(1,0),Point(1,1),Point(0,1),Point(0.75,0.5),Point(0.5,0.75),
                                   Point(0.25,0.5),Point(0.5,0.25)};
    std::vector<Point> points = square->getRegionPoints();

    EXPECT_EQ(points, expected);
}

TEST_F(CircularHoleTest, SegmentTest){
    XPolyConfig::instance()->setDiscretizationGrade(4);
    std::vector<Segment<int>> expected = {Segment<int>(0,1),Segment<int>(1,2),Segment<int>(2,3),Segment<int>(3,0),Segment<int>(4,5),Segment<int>(5,6),
                                     Segment<int>(6,7),Segment<int>(7,4)};
    std::vector<Segment<int>> segments;
    square->getSegments(segments);

    EXPECT_EQ(segments, expected);
}