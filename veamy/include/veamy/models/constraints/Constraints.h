#ifndef THESIS_CONSTRAINTS_H
#define THESIS_CONSTRAINTS_H

#include <x-poly/models/basic/Segment.h>
#include <veamy/models/dof/DOF.h>
#include <veamy/utilities/SegmentPair.h>
#include <x-poly/utilities/List.h>
#include <veamy/models/constraints/Constraint.h>
#include <veamy/models/constraints/structures/constrained_seg_mapdata.h>

class Constraints {
protected:
    std::unordered_map<Segment, Constraint, SegmentHasher> constrained_segments;
    std::unordered_map<int, Constraint, intHasher> constraints_map;
    List<int> constrained_dofs;
public:
    void addConstraint(Constraint c);
    bool isConstrained(Segment p);
    bool isConstrained(int dof);

    std::vector<int> getConstrainedDOF();
    void addConstrainedDOF(int DOF_index, DOF::Axis axis, SegmentPair pair);
    void addConstrainedDOFBySegment(int DOF_index, DOF::Axis axis, Segment s);
};


#endif
