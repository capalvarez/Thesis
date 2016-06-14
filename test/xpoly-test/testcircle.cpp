#include <gtest/gtest.h>
#include <models/polygon/Circle.h>

TEST(CircleTest, DiscretizeTest){
    Circle c (1, Point(0,0));

    std::vector<Point> points = c.discretizeCircle(2);
    std::vector<Point> p1 = {Point(1,0), Point(-1,0)};

    ASSERT_EQ(points, p1);

    std::vector<Point> points2 = c.discretizeCircle(4);
    std::vector<Point> p2 = {Point(1,0), Point(0,1), Point(-1,0), Point(0,-1)};
    ASSERT_EQ(points2, p2);
}

