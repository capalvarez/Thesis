#include "Constraint.h"


Constraint::Constraint() {}

Constraint::Constraint(Point p, Constraint::Direction d, ConstraintValue* value) {
    this->v = value;
    this->direction = d;
    this->constraints.push_back(p);
}

Constraint::Constraint(std::vector<Point> p, Constraint::Direction d, ConstraintValue* value) {
    this->v = value;
    this->direction = d;
    this->constraints.push_list(p);
}

Constraint::Constraint(Segment s, Constraint::Direction d, ConstraintValue *value) {
    this->v = value;
    this->direction = d;
}

Constraint::Constraint(std::vector<Segment> s, Constraint::Direction d, ConstraintValue *value) {
    this->v = value;
    this->direction = d;
}

double Constraint::getValue(Point p) {
    return v->getValue(p);
}

Constraint::Direction Constraint::getDirection() {
    return direction;
}

List<Point> Constraint::getPoints() {
    return this->constraints;
}



