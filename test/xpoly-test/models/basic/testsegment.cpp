#include "testsegment.h"

TEST_F(SegmentTest, ContainsPointTest){
	EXPECT_TRUE(segment->contains(segment_points, Point(0.3, 0.3)));
	EXPECT_FALSE(segment->contains(segment_points,Point(0, 1)));
	EXPECT_TRUE(segment->contains(segment_points, Point(0, 0)));
    EXPECT_TRUE(segment->contains(segment_points,Point(1, 1)));
	EXPECT_FALSE(segment->contains(segment_points,Point(2, 2)));
}

TEST_F(SegmentTest, MiddlePointTest){
	EXPECT_EQ(segment->middlePoint(segment_points), *new Point(0.5,0.5));
}

TEST_F(SegmentTest, IntersectsTest){
    PointSegment s1(Point(0,1), Point(1,0));
    PointSegment s2(Point(1,2), Point(4,0));

    Point p;
    EXPECT_TRUE(segment->intersection(segment_points, s1, p));
    EXPECT_FALSE(segment->intersection(segment_points, s2, p));
}

TEST_F(SegmentTest, IntersectionInfiniteTest){
    PointSegment s1(Point(0,0), Point(1,1));
    PointSegment s2(Point(1,3), Point(3,1));

    Point p;
    s1.intersectionInfinite(s2.getFirst(), s2.getSecond(), p);
    EXPECT_EQ(p, Point(2,2));
}




