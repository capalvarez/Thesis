#include <gtest/gtest.h>
#include <models/polygon/Triangle.h>

TEST(TriangleTest, CircumcenterTest){
    std::vector<Point> points = {Point(0,0), Point(1,0), Point(0,1), Point(0.5,1), Point(0.5,0.3),
                                 Point(1.3,0.8), Point(0.5,1.9)};

    std::vector<int> p = {0,1,2};
    Triangle t1 (p,points);
    ASSERT_EQ(t1.getCircumcenter(), Point(0.5,0.5));

    std::vector<int> p2 = {0,1,3};
    Triangle t2 (p2,points);
    ASSERT_EQ(t2.getCircumcenter(), Point(0.5,3.0/8.0));
 }


