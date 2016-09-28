#ifndef THESIS_CONSTRAINTS_H
#define THESIS_CONSTRAINTS_H

#include <x-poly/models/basic/Segment.h>
#include "Constraint.h"

class Constraints {
protected:
    std::unordered_map<Segment, Constraint, SegmentHasher> constrained_segments;
    std::unordered_map<int, Constraint, intHasher> constraints_map;
    List<int> constrained_dofs;
public:
    void addConstraint(Constraint c);
    bool isConstrained(Segment p);
    bool isConstrained(int dof);
};


#endif
