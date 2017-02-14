#ifndef THESIS_ESSENTIALCONSTRAINTS_H
#define THESIS_ESSENTIALCONSTRAINTS_H

#include <x-poly/models/basic/Point.h>
#include <unordered_map>
#include <vector>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/constraints/values/ConstraintValue.h>
#include <veamy/models/dof/DOF.h>
#include "Constraint.h"
#include "Constraints.h"
#include <veamy/utilities/SegmentPair.h>
#include <veamy/utilities/hash/veamyhashfunctions.h>

class EssentialConstraints : public Constraints{
public:
    EssentialConstraints();
    Eigen::VectorXd getBoundaryValues(std::vector<Point> points, UniqueList<DOF> dofs);
};


#endif
