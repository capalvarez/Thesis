#include "ConstraintsContainer.h"

ConstraintsContainer::ConstraintsContainer() {}

void ConstraintsContainer::addConstraints(NaturalConstraints c) {
    this->natural = c;
}

void ConstraintsContainer::addConstraints(EssentialConstraints c) {
    this->essential = c;
}

void ConstraintsContainer::addConstrainedDOF(int DOF_index, DOF::Axis axis, SegmentPair pair) {
    natural.addConstrainedDOF(DOF_index,axis,pair);
    essential.addConstrainedDOF(DOF_index,axis,pair);
}

EssentialConstraints ConstraintsContainer::getEssentialConstraints() {
    return essential;
}

NaturalConstraints ConstraintsContainer::getNaturalConstraints() {
    return natural;
}


