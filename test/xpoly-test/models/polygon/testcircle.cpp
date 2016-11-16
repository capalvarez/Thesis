#include <gtest/gtest.h>
#include <x-poly/models/polygon/Circle.h>

TEST(CircleTest, DiscretizeTest){
    XPolyConfig* config = XPolyConfig::instance();
    config->setDiscretizationGrade(2);

    Circle c (1, Point(0,0));

    std::vector<Point> points = c.discretizeCircle();
    std::vector<Point> p1 = {Point(1,0), Point(-1,0)};

    EXPECT_EQ(points, p1);

    config->setDiscretizationGrade(4);
    std::vector<Point> points2 = c.discretizeCircle();
    std::vector<Point> p2 = {Point(1,0), Point(0,1), Point(-1,0), Point(0,-1)};
    EXPECT_EQ(points2, p2);
}

