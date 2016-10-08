#ifndef THESIS_ELEMENT_H
#define THESIS_ELEMENT_H

#include <veamy/models/dof/DOF.h>
#include <veamy/models/dof/InnerDOF.h>
#include <x-poly/utilities/List.h>
#include <veamy/models/dof/DOFS.h>
#include <x-poly/models/polygon/Polygon.h>
#include <veamy/models/dof/VertexDOF.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/utilities/SegmentPair.h>
#include <veamy/physics/BodyForce.h>
#include <iostream>
#include <veamy/matrix/integration/IntegrationFunction.h>
#include <veamy/models/constraints/NaturalConstraints.h>
#include <veamy/models/constraints/ConstraintsContainer.h>

class Element {
private:
    std::vector<int> dofs;
    Eigen::MatrixXd K;
    Eigen::VectorXd f;

    void initMatrix(DOFS d, std::vector<Point> points, std::vector<double> weight, Polygon p, BodyForce* f,
                    ConstraintsContainer constrains);
public:
    Element(ConstraintsContainer& constraints, Polygon p, List<Point>& points, DOFS& out, BodyForce* f);
    Eigen::MatrixXd getK();
    Eigen::VectorXd getF();
    void assembleK(DOFS out, Eigen::MatrixXd& Kglobal);
    void assembleF(DOFS out, Eigen::VectorXd& Fglobal);
};


#endif
