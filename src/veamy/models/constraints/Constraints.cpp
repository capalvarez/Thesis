#include "Constraints.h"


Constraints::Constraints() {}

void Constraints::addConstraint(Constraint *c) {
    c->addToMap(this->constrained_points);
}

bool Constraints::isConstrained(Point p) {
    return constrained_points.find(p)!=constrained_points.end();
}


std::vector<int> Constraints::getConstrainedDOF() {
    return constrained_dofs.getList();
}

void Constraints::addConstrainedDOF(int DOF_index) {
    constrained_dofs.push_back(DOF_index);
}


