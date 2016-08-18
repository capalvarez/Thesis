#include "testvempolygon.h"

TEST_F(VEMPolygonTest, TriangulateTest){
    std::vector<IntegrationTriangle> triangle;
    square->triangulate(triangle,points);
    std::vector<IntegrationTriangle> expected = {IntegrationTriangle(3,0,1), IntegrationTriangle(1,2,3)};

    EXPECT_EQ(triangle, expected);

    triangle.clear();
    nonconvex->triangulate(triangle,points);
    std::vector<IntegrationTriangle> expected2 = {IntegrationTriangle(0,1,4), IntegrationTriangle(3,0,4),
                                                  IntegrationTriangle(4,2,3)};
    EXPECT_EQ(triangle, expected2);
}

TEST_F(VEMPolygonTest, AverageTest){
    double (*f)(double, double);
    f = testfunctions::sum;

    EXPECT_FLOAT_EQ(square->getAverage(f,points), 1);
}
