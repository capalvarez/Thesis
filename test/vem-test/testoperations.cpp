#include <gtest/gtest.h>
#include <x-poly/models/basic/Point.h>
#include <x-poly/models/polygon/Polygon.h>
#include <veamy/utilities/operations.h>

TEST(OperationsTest, DotTest){

}

TEST(OperationsTest, GradientTest){
    std::vector<Point> points = {Point(0,0), Point(1,0), Point(1,1), Point(0,1)};
    std::vector<int> point_index = {0, 1, 2, 3};

    Polygon p (point_index, points);
    Pair<double> result = operations::gradient(Pair<int>(1,0), p, points[0]);
    Pair<double> expected = Pair<double>(1/sqrt(2),0);

    EXPECT_EQ(result, expected);
}

TEST(OperationsTest, LaplacianTest){

}

