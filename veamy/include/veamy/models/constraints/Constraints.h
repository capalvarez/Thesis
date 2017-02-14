#ifndef THESIS_CONSTRAINTS_H
#define THESIS_CONSTRAINTS_H

#include <x-poly/models/basic/Segment.h>
#include <veamy/models/dof/DOF.h>
#include <veamy/utilities/SegmentPair.h>
#include <utilities/UniqueList.h>
#include <veamy/models/constraints/Constraint.h>
#include <veamy/models/constraints/structures/constrained_seg_mapdata.h>
#include <veamy/models/constraints/structures/isConstrainedInfo.h>
#include <x-poly/voronoi/structures/mapdata.h>


class Constraints {
protected:
    std::vector<IndexSegment> constrained_segments;

    std::unordered_map<IndexSegment, Constraint, SegmentHasher> segment_map;
    std::unordered_map<int, Constraint, intHasher> constraints_map;
    UniqueList<int> constrained_dofs;
public:
    void addConstraint(Constraint c);
    isConstrainedInfo isConstrained(std::vector<Point> points, IndexSegment p);
    bool isConstrained(int dof);

    std::vector<int> getConstrainedDOF();
    void addConstrainedDOF(std::vector<Point> points, int DOF_index, DOF::Axis axis, SegmentPair pair);
    void addConstrainedDOFBySegment(std::vector<Point> points, int DOF_index, DOF::Axis axis, IndexSegment s);
};


#endif
