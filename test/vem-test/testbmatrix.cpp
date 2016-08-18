#include <gtest/gtest.h>
#include <x-poly/models/basic/Point.h>
#include <x-poly/models/polygon/Polygon.h>
#include <matrix/BMatrix.h>


TEST(BMatrixTest, InitializationTest){
    std::vector<Point> points = {Point(0,0), Point(1,0), Point(1,1), Point(0,1)};
    std::vector<int> point_index = {0, 1, 2, 3};

    Polygon p (point_index, points);

  /*  BMatrix b (p, 1, points);

    Eigen::MatrixXf expected(3,4);
    double v = 1/(2*sqrt(2));
    expected << 4, 4, 4, 4,
            -v, v, v, -v,
            -v, -v, v ,v;

    EXPECT_EQ(b.getBMatrix(), expected);*/

    BMatrix b2 (p,2,points);

    std::cout << b2.getBMatrix() << std::endl;
}



