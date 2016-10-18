#include "testsegment.h"

TEST_F(SegmentTest, ContainsPointTest){
	EXPECT_TRUE(segment->contains(segment_points, Point(0.3,0.3)));
	EXPECT_FALSE(segment->contains(segment_points, Point(0,1)));
	EXPECT_TRUE(segment->contains(segment_points, Point(0,0)));
    EXPECT_TRUE(segment->contains(segment_points, Point(1,1)));
	EXPECT_FALSE(segment->contains(segment_points, Point(2,2)));
}

TEST_F(SegmentTest, MiddlePointTest){
	EXPECT_EQ(segment->middlePoint(segment_points), *new Point(0.5,0.5));
}

TEST_F(SegmentTest, IntersectsTest){
    Segment<Point> s1(Point(0,1), Point(1,0));
    Segment<Point> s2(Point(1,2), Point(4,0));

    Point p;
    EXPECT_TRUE(segment->intersection(segment_points, s1, p));
    EXPECT_FALSE(segment->intersection(segment_points, s2, p));


}



