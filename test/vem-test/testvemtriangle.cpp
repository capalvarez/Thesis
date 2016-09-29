#include <gtest/gtest.h>
#include <x-poly/models/basic/Point.h>
#include <veamy/matrix/integration/IntegrationTriangle.h>

TEST(VEMTriangleTest, IntegrateTest){
    class Sum : public IntegrationFunction{
    public:
        double call(double x, double y){
            return x + y;
        }
    };

    class Norm : public IntegrationFunction{
        double call(double x, double y){
            return pow(x,2) + pow(y,2);
        }
    };

    std::vector<Point> points = {Point(0,0),Point(1,0),Point(2,0),Point(1,1),Point(0,1)};

    IntegrationTriangle t(0,1,4);
    IntegrationTriangle t2(0,2,3);
    Sum* f = new Sum();
    EXPECT_FLOAT_EQ(t.integrate(f,points),1.0/3);
    EXPECT_FLOAT_EQ(t2.integrate(f,points),8.0/6);
    delete(f);

    Norm* f2 = new Norm();
    EXPECT_FLOAT_EQ(t.integrate(f2,points),1/6.0);
    EXPECT_FLOAT_EQ(t2.integrate(f2,points),4.0/3);
}

