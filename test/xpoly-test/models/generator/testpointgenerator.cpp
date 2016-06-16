#include "testpointgenerator.h"

TEST_F(PointGeneratorTest, GenerateTest){
    std::vector<Point> res;
    const_const->generate(res,*box,3,3);

    std::vector<Point> exp = {Point(0,0),Point(5,0),Point(10,0),Point(0,5),Point(5,5),Point(10,5),
                              Point(0,10),Point(5,10),Point(10,10)};
    EXPECT_EQ(res, exp);


}