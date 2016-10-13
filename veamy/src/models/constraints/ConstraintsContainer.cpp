#include <veamy/models/constraints/ConstraintsContainer.h>

ConstraintsContainer::ConstraintsContainer() {}

void ConstraintsContainer::addConstraints(NaturalConstraints c) {
    this->natural = c;
}

void ConstraintsContainer::addConstraints(EssentialConstraints c) {
    this->essential = c;
}

void ConstraintsContainer::addConstrainedDOF(std::vector<Point> points, int DOF_index, DOF::Axis axis, SegmentPair<int> pair) {
    natural.addConstrainedDOF(points, DOF_index,axis,pair);
    essential.addConstrainedDOF(points, DOF_index,axis,pair);
}

EssentialConstraints ConstraintsContainer::getEssentialConstraints() {
    return essential;
}

NaturalConstraints ConstraintsContainer::getNaturalConstraints() {
    return natural;
}


