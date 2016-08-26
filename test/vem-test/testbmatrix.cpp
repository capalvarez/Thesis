#include <gtest/gtest.h>
#include <x-poly/models/basic/Point.h>
#include <x-poly/models/polygon/Polygon.h>
#include <matrix/BMatrix.h>
#include <matrix/dof/VertexDOF.h>
#include <matrix/dof/EdgeDOF.h>
#include <matrix/dof/InnerDOF.h>


TEST(BMatrixTest, InitializationTest){
    std::vector<Point> points = {Point(0,0), Point(1,0), Point(1,1), Point(0,1)};
    std::vector<int> point_index = {0, 1, 2, 3};

    Polygon p (point_index, points);
    /*BasePolinomials base(1);
    std::vector<DOF*> dofs = {new VertexDOF(0), new VertexDOF(1), new VertexDOF(2), new VertexDOF(3)};

    BMatrix b (1, dofs, p, base, points);

    Eigen::MatrixXd expected(3,4);
    double v = 1/(2*sqrt(2));
    expected << 0.25, 0.25, 0.25, 0.25,
            -v, v, v, -v,
            -v, -v, v ,v;

    EXPECT_EQ(b.getBMatrix(), expected);*/

    BasePolinomials base2(2);

    points.push_back(Point(0.5,0));
    points.push_back(Point(1,0.5));
    points.push_back(Point(0.5,1));
    points.push_back(Point(0,0.5));

    std::vector<DOF*> dofs2 = {new VertexDOF(0), new VertexDOF(1), new VertexDOF(2), new VertexDOF(3), new EdgeDOF(4),
                               new EdgeDOF(5), new EdgeDOF(6), new EdgeDOF(7), new InnerDOF(Pair<int>(0,0,1))};

    BMatrix b2 (2, dofs2, p, base2, points);

    //std::cout << b2.getBMatrix() << std::endl;

}



