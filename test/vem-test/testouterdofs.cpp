#include <gtest/gtest.h>
#include <veamy/models/dof/DOFS.h>

TEST(OuterDOFTest, AddVertexDOFTest){
    DOFS outer;
    Constraints c;
    std::vector<Point> points;

    outer.addVertexDOF(c,points,3);
    outer.addVertexDOF(c,points,2);
    outer.addVertexDOF(c,points,3);

    List<DOF*> list = outer.getDOFS();
    EXPECT_EQ(list.size(),2);
}

