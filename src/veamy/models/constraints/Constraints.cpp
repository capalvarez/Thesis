#include "Constraints.h"

void Constraints::addConstraint(Constraint c) {
    List<Segment> segments = c.getSegments();

    for (int i = 0; i < segments.size(); ++i) {
        constrained_segments.insert(std::make_pair(segments.get(i), c));
    }
}

bool Constraints::isConstrained(Segment s) {
    return constrained_segments.find(s)!=constrained_segments.end();
}

bool Constraints::isConstrained(int dof) {
    return constrained_dofs.contains(dof);
}

