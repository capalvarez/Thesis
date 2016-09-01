#include <x-poly/models/basic/Point.h>
#include <vector>
#include <gtest/gtest.h>
#include <x-poly/models/polygon/Polygon.h>
#include <matrix/DMatrix.h>
#include <lib/Eigen/Dense>
#include <matrix/dof/DOF.h>
#include <matrix/dof/VertexDOF.h>
#include <matrix/dof/EdgeDOF.h>
#include <matrix/dof/InnerDOF.h>

TEST(DMatrixTest, InitializationTest){
    std::vector<Point> points = {Point(0,0), Point(1,0), Point(1,1), Point(0,1)};
    std::vector<int> point_index = {0, 1, 2, 3};

    Polygon p (point_index, points);
    BasePolinomials b(1);

    std::vector<DOF*> dofs = {new VertexDOF(0), new VertexDOF(1), new VertexDOF(2), new VertexDOF(3)};

    DMatrix d (dofs, p, b, points);
    Eigen::MatrixXd expected(4,3);

    double value = 1/(2*sqrt(2));
    expected << 1, -value, -value,
            1, value, -value,
            1, value, value,
            1, -value, value;

    EXPECT_EQ(d.getDMatrix(), expected);

    BasePolinomials b2 (2);

    points.push_back(Point(0.5,0));
    points.push_back(Point(1,0.5));
    points.push_back(Point(0.5,1));
    points.push_back(Point(0,0.5));

    std::vector<DOF*> dofs2 = {new VertexDOF(0), new VertexDOF(1), new VertexDOF(2), new VertexDOF(3), new EdgeDOF(4),
                               new EdgeDOF(5), new EdgeDOF(6), new EdgeDOF(7), new InnerDOF(Pair<int>(0,0),1)};

    DMatrix d2 (dofs2, p, b2, points);

    Eigen::MatrixXd expected2(9,6);
    double v = 1/8.0;

    expected2.row(0) << 1, -value, -value, v, v, v;
    expected2.row(1) << 1, value, - value, v, -v, v;
    expected2.row(2) << 1, value, value, v, v, v;
    expected2.row(3) << 1, -value, value, v, -v, v;
    expected2.row(4) << 1, 0, -value, 0, 0, v;
    expected2.row(5) << 1, value, 0, v, 0, 0;
    expected2.row(6) << 1, 0, value, 0, 0, v;
    expected2.row(7) << 1, -value, 0, v, 0, 0;
    expected2.row(8) << 1, 0, 0, 1/24.0, 0, 1/24.0;

    EXPECT_TRUE(d2.getDMatrix().isApprox(expected2,0.0001));
}

