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
#include <utilities/SegmentPair.h>

class EssentialConstraints {
private:
    std::unordered_map<Segment, Constraint, SegmentHasher> constrained_segments;
    std::unordered_map<int, Constraint, intHasher> constraints_map;
    List<int> constrained_dofs;
public:
    EssentialConstraints();
    void addConstraint(Constraint c);
    bool isConstrained(Segment p);
    std::vector<int> getConstrainedDOF();
    void addConstrainedDOF(int DOF_index, DOF::Axis axis, SegmentPair pair);
    void addConstrainedDOFBySegment(int DOF_index, DOF::Axis axis, Segment s);

    Eigen::VectorXd getBoundaryValues(std::vector<Point> points, List<DOF*> dofs);
};


#endif
