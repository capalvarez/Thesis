#include <gtest/gtest.h>
#include <matrix/dof/DOFS.h>

TEST(OuterDOFTest, AddVertexDOFTest){
    DOFS outer;
    outer.addVertexDOF(3);
    outer.addVertexDOF(2);
    outer.addVertexDOF(3);

    List<DOF*> list = outer.getDOFS();
    EXPECT_EQ(list.size(),2);
}

