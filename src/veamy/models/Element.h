#ifndef THESIS_ELEMENT_H
#define THESIS_ELEMENT_H

#include <veamy/models/dof/DOF.h>
#include <models/dof/InnerDOF.h>
#include <x-poly/utilities/List.h>
#include <models/dof/DOFS.h>
#include <x-poly/models/polygon/Polygon.h>
#include <models/dof/VertexDOF.h>
#include <matrix/lobattoQuadrature.h>
#include <matrix/BasePolinomials.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/utilities/SegmentPair.h>
#include <physics/BodyForce.h>
#include <iostream>
#include <matrix/integration/IntegrationFunction.h>
#include <models/constraints/NaturalConstraints.h>
#include <models/constraints/ConstraintsContainer.h>

class Element {
private:
    std::vector<int> dofs;
    Eigen::MatrixXd K;
    Eigen::VectorXd f;

    void initMatrix(DOFS d, std::vector<Point> points, std::vector<double> weight, Polygon p, int k, BodyForce* f,
                    ConstraintsContainer constrains);
public:
    Element(ConstraintsContainer& constraints, Polygon p, List<Point>& points, DOFS& out, int k, BodyForce* f);
    Eigen::MatrixXd getK();
    Eigen::VectorXd getF();
    void assembleK(DOFS out, Eigen::MatrixXd& Kglobal);
    void assembleF(DOFS out, Eigen::VectorXd& Fglobal);
};


#endif
