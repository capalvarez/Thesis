#include <x-poly/models/basic/Point.h>
#include <vector>
#include <gtest/gtest.h>
#include <x-poly/models/polygon/Polygon.h>
#include <matrix/DMatrix.h>
#include <lib/Eigen/Dense>

TEST(DMatrixTest, InitializationTest){
    std::vector<Point> points = {Point(0,0), Point(1,0), Point(1,1), Point(0,1)};
    std::vector<int> point_index = {0, 1, 2, 3};

    Polygon p (point_index, points);

    //DMatrix d (p, 1, points);
    Eigen::MatrixXf expected(4,3);

    double value = 1/(2*sqrt(2));
    expected << 1, -value, -value,
            1, value, -value,
            1, value, value,
            1, -value, value;

   // EXPECT_EQ(d.getDMatrix(), expected);

    DMatrix d2 (p,2,points);

    //std::cout << d2.getDMatrix() << std::endl;
}

