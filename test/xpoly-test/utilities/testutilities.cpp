#include <gtest/gtest.h>
#include <x-poly/utilities/utilities.h>

TEST(UtilitiesTest, RandomIntegerTest){
    int r = utilities::random_integer(0,10);
    int r1 = utilities::random_integer(0,10);
    int r2 = utilities::random_integer(0,10);
    int r3 = utilities::random_integer(0,10);
}
