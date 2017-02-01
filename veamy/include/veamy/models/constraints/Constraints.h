#ifndef THESIS_CONSTRAINTS_H
#define THESIS_CONSTRAINTS_H

#include <x-poly/models/basic/Segment.h>
#include <veamy/models/dof/DOF.h>
#include <veamy/utilities/SegmentPair.h>
#include "../../../../../utilities/include/utilities/UniqueList.h"
#include <veamy/models/constraints/Constraint.h>
#include <veamy/models/constraints/structures/constrained_seg_mapdata.h>
#include <veamy/models/constraints/structures/isConstrainedInfo.h>
#include <x-poly/voronoi/structures/mapdata.h>

class Constraints {
protected:
    std::vector<Segment<int>> constrained_segments;

    std::unordered_map<Segment<int>, Constraint, SegmentHasher> segment_map;
    std::unordered_map<int, Constraint, intHasher> constraints_map;
    UniqueList<int> constrained_dofs;
public:
    void addConstraint(Constraint c);
    isConstrainedInfo isConstrained(std::vector<Point> points, Segment<int> p);
    bool isConstrained(int dof);

    std::vector<int> getConstrainedDOF();
    void addConstrainedDOF(std::vector<Point> points, int DOF_index, DOF::Axis axis, SegmentPair<int> pair);
    void addConstrainedDOFBySegment(std::vector<Point> points, int DOF_index, DOF::Axis axis, Segment<int> s);
};


#endif
