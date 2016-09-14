#include "PointConstraint.h"

PointConstraint::PointConstraint(Point p, Constraint::Direction d, ConstraintValue* value) {
    this->v = value;
}

PointConstraint::PointConstraint(std::vector<Point> p, Constraint::Direction d, ConstraintValue* value) {
    this->v = value;
}

double PointConstraint::getValue(Point p) {
    return v->getValue(p);
}


