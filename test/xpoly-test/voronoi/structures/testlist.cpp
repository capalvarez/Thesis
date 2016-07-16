#include "testlist.h"

TEST_F(ListTest, PushBackTest){
    std::vector<Point> expected = {Point(0,0), Point(1,0), Point(1,1), Point(2,0)};
    EXPECT_EQ(list->getList(), expected);
}

TEST_F(ListTest, SizeTest){
    EXPECT_EQ(list->size(),4);
}

TEST_F(ListTest, AccessTest){
    EXPECT_EQ(list->get(2), Point(1,1));
    EXPECT_EQ(list->get(3), Point(2,0));
}

