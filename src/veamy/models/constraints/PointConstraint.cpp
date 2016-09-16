#include "PointConstraint.h"

PointConstraint::PointConstraint(Point p, Constraint::Direction d, ConstraintValue* value) {
    this->v = value;
    this->direction = d;
    this->constraints.push_back(p);
}

PointConstraint::PointConstraint(std::vector<Point> p, Constraint::Direction d, ConstraintValue* value) {
    this->v = value;
    this->direction = d;
    this->constraints.assign(p.begin(),p.end());
}

double PointConstraint::getValue(Point p) {
    return v->getValue(p);
}

void PointConstraint::addToMap(std::unordered_map<Point, Constraint *, PointHasher> map) {
    for (int i = 0; i < this->constraints.size(); ++i) {
        map.insert(std::make_pair(this->constraints[i],this));
    }
}



