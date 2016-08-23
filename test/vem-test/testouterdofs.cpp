#include <gtest/gtest.h>
#include <matrix/dof/OuterDOFS.h>

TEST(OuterDOFTest, AddVertexDOFTest){
    OuterDOFS outer;
    outer.addVertexDOF(3);
    outer.addVertexDOF(2);
    outer.addVertexDOF(3);

    List<OuterDOF*> list = outer.getDOFS();
    EXPECT_EQ(list.size(),2);
}

