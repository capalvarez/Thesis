#include "testpointgenerator.h"

TEST_F(PointGeneratorTest, GenerateTest){
    std::vector<Point> res;

    PointGenerator a (functions::constant(), functions::constant());
    a.generate(res,*box,3,3);

    std::vector<Point> exp = {Point(0,0),Point(5,0),Point(10,0),Point(0,5),Point(5,5),Point(10,5),
                              Point(0,10),Point(5,10),Point(10,10)};
    EXPECT_EQ(res, exp);

    /*BoundingBox* box = new BoundingBox(Point(0,0), Point(1,1));
    PointGenerator* ran_ran = new PointGenerator(functions::random_double(0,1), functions::random_double(0,1));
    std::vector<Point> p;
    ran_ran->generate(p,*box,3,3);

    for(int i=0;i<9;i++){
        std::cout << p[i].getString() << std::endl;
    }*/
}