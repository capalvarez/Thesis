#include <gtest/gtest.h>
#include <veamy/matrix/BasePolinomials.h>

TEST(BasisPolinomials, CreationTest){
    BasePolinomials linear (1);
    std::vector<Pair<int>> linear_vector = {Pair<int>(0,0), Pair<int>(1,0), Pair<int>(0,1)};

    EXPECT_EQ(linear_vector, linear.getPolinomials());

    BasePolinomials quadratic (2);
    std::vector<Pair<int>> quadratic_vector = {Pair<int>(0,0), Pair<int>(1,0), Pair<int>(0,1),
                                               Pair<int>(2,0), Pair<int>(1,1), Pair<int>(0,2)};

    EXPECT_EQ(quadratic_vector, quadratic.getPolinomials());
}

