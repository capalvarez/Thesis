#ifndef THESIS_ELEMENT_H
#define THESIS_ELEMENT_H

#include <veamy/models/dof/DOF.h>
#include <x-poly/utilities/List.h>
#include <veamy/models/dof/DOFS.h>
#include <x-poly/models/polygon/Polygon.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/utilities/SegmentPair.h>
#include <veamy/physics/BodyForce.h>
#include <iostream>
#include <veamy/models/constraints/NaturalConstraints.h>
#include <veamy/models/constraints/ConstraintsContainer.h>
#include <veamy/physics/ProblemConditions.h>

class Element {
private:
    std::vector<int> dofs;
    Eigen::MatrixXd K;
    Eigen::VectorXd f;

    void initMatrix(DOFS d, std::vector<Point> points, Polygon p, ProblemConditions& conditions);
public:
    Element(ProblemConditions& conditions, Polygon p, List<Point>& points, DOFS& out);
    void assembleK(DOFS out, Eigen::MatrixXd& Kglobal);
    void assembleF(DOFS out, Eigen::VectorXd& Fglobal);
};


#endif
