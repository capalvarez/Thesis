#include "testdegreesoffreedom.h"
#include "utilities/Pair.h"

TEST_F(DegreesOfFreedomTest, LobattoTest){

}

TEST_F(DegreesOfFreedomTest, NormalTest){
    EXPECT_EQ(degreesSquare->normal(0,points), Pair<double>(-0.5,-0.5));

}

