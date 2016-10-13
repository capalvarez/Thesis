#include <gtest/gtest.h>
#include <x-poly/models/generator/Functor.h>
#include <x-poly/models/generator/functions.h>

TEST(FunctionsTest, FunctionListTest){
    EXPECT_EQ(functions::constant()->apply(3), 3);
    EXPECT_EQ(functions::uniform(5)->apply(1),5);

    EXPECT_EQ(functions::sine(1,10,0)->apply(0), 0);
    EXPECT_EQ(functions::sine(1,1,0)->apply(90), 1);
    EXPECT_NEAR(functions::sine(1,2,0)->apply(90), 0.0, 0.0001);
}

