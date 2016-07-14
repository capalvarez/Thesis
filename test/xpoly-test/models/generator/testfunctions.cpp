#include <gtest/gtest.h>
#include <x-poly/models/generator/Functor.h>
#include <x-poly/models/generator/functions.h>

TEST(FunctionsTest, FunctionListTest){
    EXPECT_EQ((*functions::constant())(3), 3);
    EXPECT_EQ((*functions::uniform(5))(1),5);

    EXPECT_EQ((*functions::sine(1,10,0))(0), 0);
    EXPECT_EQ((*functions::sine(1,1,0))(90), 1);
    EXPECT_NEAR((*functions::sine(1,2,0))(90), 0.0, 0.0001);
}

