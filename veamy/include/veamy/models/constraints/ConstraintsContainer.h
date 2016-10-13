#ifndef THESIS_CONSTRAINTSCONTAINER_H
#define THESIS_CONSTRAINTSCONTAINER_H

#include "EssentialConstraints.h"
#include "NaturalConstraints.h"

class ConstraintsContainer {
private:
    EssentialConstraints essential;
    NaturalConstraints natural;
public:
    ConstraintsContainer();
    void addConstraints(NaturalConstraints c);
    void addConstraints(EssentialConstraints c);

    void addConstrainedDOF(std::vector<Point> points, int DOF_index,DOF::Axis axis, SegmentPair<int> pair);

    EssentialConstraints getEssentialConstraints();
    NaturalConstraints getNaturalConstraints();
};


#endif
