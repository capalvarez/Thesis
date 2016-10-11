#include <veamy/models/constraints/Constraint.h>

Constraint::Constraint() {}

Constraint::Constraint(Segment s, Constraint::Direction d, ConstraintValue *value) {
    this->v = value;
    this->direction = d;
    this->constraints.push_back(s);
}

Constraint::Constraint(std::vector<Segment> s, Constraint::Direction d, ConstraintValue *value) {
    this->v = value;
    this->direction = d;
    this->constraints.push_list(s);
}

double Constraint::getValue(Point p) {
    return v->getValue(p);
}

Constraint::Direction Constraint::getDirection() {
    return direction;
}

List<Segment> Constraint::getSegments() {
    return this->constraints;
}

Pair<int> Constraint::getIndex(int point_index) {
    switch(direction){
        case Horizontal:
            return Pair<int>(2*point_index, -1);
        case Vertical:
            return Pair<int>(-1, 2*point_index+1);
        case Total:
            return Pair<int>(2*point_index, 2*point_index+1);
    }

    return Pair<int>(-1,-1);
}





