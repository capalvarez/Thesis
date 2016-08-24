#ifndef THESIS_ELEMENT_H
#define THESIS_ELEMENT_H

#include <veamy/matrix/dof/DOF.h>
#include <matrix/dof/InnerDOF.h>
#include <x-poly/utilities/List.h>
#include <matrix/dof/OuterDOFS.h>
#include <x-poly/models/polygon/Polygon.h>
#include <matrix/dof/VertexDOF.h>
#include <matrix/lobattoQuadrature.h>
#include <matrix/BasePolinomials.h>
#include <veamy/lib/Eigen/Dense>

class Element {
private:
    std::vector<int> outerDofs;
    std::vector<InnerDOF*> innerDofs;

    Eigen::MatrixXd K;
    void initMatrizAndVector(std::vector<DOF*> dofs, std::vector<Point> points, std::vector<double> weight,
                             Polygon p, int k);
    std::vector<DOF*> getDOFS(OuterDOFS o);
public:
    Element(Polygon p, List<Point>& points, OuterDOFS& out, int k);
    Eigen::MatrixXd getK();
    void assembleK(OuterDOFS out, Eigen::MatrixXd& Kglobal);
};


#endif
