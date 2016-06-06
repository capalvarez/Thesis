#include "testsegment.h"

TEST_F(SegmentTest, ContainsPointTest){
	EXPECT_TRUE(segment->contains(segment_points, Point(0.3,0.3)));
	EXPECT_FALSE(segment->contains(segment_points, Point(0,1)));
	EXPECT_FALSE(segment->contains(segment_points, Point(2,2)));
}

TEST_F(SegmentTest, MiddlePointTest){
	ASSERT_EQ(segment->middlePoint(segment_points), Point(0.5,0.5));
}




