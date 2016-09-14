#ifndef THESIS_CONSTRAINTS_H
#define THESIS_CONSTRAINTS_H

#include <x-poly/models/basic/Point.h>
#include <unordered_map>
#include <vector>
#include <x-poly/utilities/List.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/constraints/values/ConstraintValue.h>
#include <veamy/models/dof/DOF.h>
#include "Constraint.h"
#include "models/constraints/structures/mapdata.h"

class Constraints {
private:
    std::unordered_map<Point, Constraint*, PointHasher> constrained_points;
    std::unordered_map<int, Constraint*, intHasher> constraints_map;
    List<int> constrained_dofs;
public:
    Constraints();
    void addConstraint(Constraint* c);
    bool isConstrained(Point p);
    std::vector<int> getConstrainedDOF();
    void addConstrainedDOF(Point p, int DOF_index, DOF::Axis axis);

    Eigen::VectorXd getBoundaryValues(std::vector<Point> points, List<DOF*> dofs);
};


#endif
