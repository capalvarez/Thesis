#include <gtest/gtest.h>
#include <utilities/RandomGenerator.h>
#include <utilities/utilities.h>

TEST(RandomTest, RandomIntegerTest){
    std::cout << utilities::random_integer(0,10) << std::endl;
    std::cout << utilities::random_integer(0,10) << std::endl;
    std::cout << utilities::random_integer(0,10) << std::endl;
    std::cout << utilities::random_integer(0,10) << std::endl;
    std::cout << utilities::random_integer(0,10) << std::endl;
    std::cout << utilities::random_integer(0,10) << std::endl;
    std::cout << utilities::random_integer(0,10) << std::endl;
    std::cout << utilities::random_integer(0,10) << std::endl;
    std::cout << utilities::random_integer(0,10) << std::endl;
}