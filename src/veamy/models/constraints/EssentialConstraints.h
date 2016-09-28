#ifndef THESIS_ESSENTIALCONSTRAINTS_H
#define THESIS_ESSENTIALCONSTRAINTS_H

#include <x-poly/models/basic/Point.h>
#include <unordered_map>
#include <vector>
#include <x-poly/utilities/List.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/constraints/values/ConstraintValue.h>
#include <veamy/models/dof/DOF.h>
#include "Constraint.h"
#include "models/constraints/structures/mapdata.h"
#include "Constraints.h"
#include <utilities/SegmentPair.h>

class EssentialConstraints : public Constraints{
public:
    EssentialConstraints();
    std::vector<int> getConstrainedDOF();
    void addConstrainedDOF(int DOF_index, DOF::Axis axis, SegmentPair pair);
    void addConstrainedDOFBySegment(int DOF_index, DOF::Axis axis, Segment s);

    Eigen::VectorXd getBoundaryValues(std::vector<Point> points, List<DOF*> dofs);
};


#endif
