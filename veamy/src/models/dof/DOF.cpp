#include <veamy/models/dof/DOF.h>


DOF::DOF(int index, int point_index, DOF::Axis a) {
    this->index = index;
    this->point_index = point_index;
    this->d = a;
}

int DOF::globalIndex() {
    return this->index;
}

int DOF::pointIndex() {
    return this->point_index;
}

bool DOF::operator==(const DOF &other) const {
    return this->index == other.index;
}




