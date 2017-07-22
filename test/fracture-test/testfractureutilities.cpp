#include <gtest/gtest.h>
#include <utilities/Pair.h>
#include <fracture/utilities/fractureutilities.h>

TEST(FractureUtilitiesTest, AllPairsTest){
    std::vector<int> val = {3,9,5,14};
    std::vector<Pair<int>> pairs;

    fracture_utilities::allPairs(pairs, val);
    std::vector<Pair<int>> expected = {Pair<int>(3,9), Pair<int>(3,5), Pair<int>(3,14), Pair<int>(9,5), Pair<int>(9,14),
                                       Pair<int>(5,14)};
    EXPECT_EQ(pairs, expected);

}