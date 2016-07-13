#include "testvempolygon.h"

TEST_F(VEMPolygonTest, TriangulateTest){
    std::vector<VEMTriangle> triangle;
    square->triangulate(triangle,points);
    std::vector<VEMTriangle> expected = {VEMTriangle(4,0,1), VEMTriangle(4,1,2), VEMTriangle(4,2,3), VEMTriangle(4,3,0)};

    EXPECT_EQ(triangle, expected);
}

TEST_F(VEMPolygonTest, AverageTest){
    double (*f)(double, double);
    f = testfunctions::sum;

    EXPECT_FLOAT_EQ(square->getAverage(f,points), 1);
}
