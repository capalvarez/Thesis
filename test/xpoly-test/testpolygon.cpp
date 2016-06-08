#include "testpolygon.h"

TEST_F(PolygonTest, AreaTest){
    EXPECT_EQ(triangle->getArea(),0.5);
    EXPECT_EQ(square->getArea(),1);
    EXPECT_EQ(nonconvex->getArea(),1.5);
}

TEST_F(PolygonTest, IsConvexTest){
    EXPECT_TRUE(triangle->isConvex(points));
    EXPECT_EQ(square->isConvex(points), true);
    EXPECT_EQ(nonconvex->isConvex(points), false);
}

