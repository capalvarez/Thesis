#include "testsegment.h"

TEST_F(SegmentTest, ContainsPointTest){
	EXPECT_TRUE(segment->contains(Point(0.3, 0.3), Point(), Point()));
	EXPECT_FALSE(segment->contains(Point(0, 1), Point(), Point()));
	EXPECT_TRUE(segment->contains(Point(0, 0), Point(), Point()));
    EXPECT_TRUE(segment->contains(Point(1, 1), Point(), Point()));
	EXPECT_FALSE(segment->contains(Point(2, 2), Point(), Point()));
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

TEST_F(SegmentTest, CartesianAngleTest){
    EXPECT_EQ(segment->cartesianAngle(segment_points),45);
    EXPECT_EQ(Segment<int>(0,2).cartesianAngle(segment_points),135);
    EXPECT_EQ(Segment<int>(0,3).cartesianAngle(segment_points),225);
    EXPECT_EQ(Segment<int>(0,4).cartesianAngle(segment_points),315);

}



