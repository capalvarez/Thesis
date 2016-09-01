#ifndef THESIS_ELEMENT_H
#define THESIS_ELEMENT_H

#include <veamy/matrix/dof/DOF.h>
#include <matrix/dof/InnerDOF.h>
#include <x-poly/utilities/List.h>
#include <matrix/dof/DOFS.h>
#include <x-poly/models/polygon/Polygon.h>
#include <matrix/dof/VertexDOF.h>
#include <matrix/lobattoQuadrature.h>
#include <matrix/BasePolinomials.h>
#include <veamy/lib/Eigen/Dense>

class Element {
private:
    std::vector<int> dofs;

    Eigen::MatrixXd K;
    Eigen::MatrixXd f;
    void initMatrix(DOFS d, std::vector<Point> points, std::vector<double> weight, Polygon p, int k);
    void initVector();
public:
    Element(Polygon p, List<Point>& points, DOFS& out, int k);
    Eigen::MatrixXd getK();
    Eigen::VectorXd getF();
    void assembleK(DOFS out, Eigen::MatrixXd& Kglobal);
    void assembleF(DOFS out, Eigen::VectorXd& Fglobal);
};


#endif
