#include <veamy/models/constraints/Constraint.h>
#include <assert.h>


Constraint::Constraint() {}

Constraint::Constraint(Segment<int> s, Constraint::Direction d, ConstraintValue *value) {
    this->v = value;
    this->direction = d;
    this->constraints.push_back(s);
}

Constraint::Constraint(std::vector<Segment<int>> s, Constraint::Direction d, ConstraintValue *value) {
    this->v = value;
    this->direction = d;
    this->constraints.push_list(s);
}

Constraint::Constraint(Segment<Point> s, std::vector<Point> points, Constraint::Direction d, ConstraintValue *value) {
    this->v = value;
    this->direction = d;
    Segment<int> int_segment = fromPointToInt(s, points);
    this->constraints.push_back(int_segment);
}

Constraint::Constraint(std::vector<Segment<Point>> s, std::vector<Point> points, Constraint::Direction d,
                       ConstraintValue *value) {
    this->v = value;
    this->direction = d;

    for(int i = 0; i<s.size(); i++){
        Segment<int> int_segment = fromPointToInt(s[i], points);
        this->constraints.push_back(int_segment);
    }
}

double Constraint::getValue(Point p) {
    return v->getValue(p);
}

Constraint::Direction Constraint::getDirection() {
    return direction;
}

UniqueList<Segment<int>> Constraint::getSegments() {
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

Segment<int> Constraint::fromPointToInt(Segment<Point> s, std::vector<Point> points) {
    int p1 = utilities::indexOf(points, s.getFirst());
    int p2 = utilities::indexOf(points, s.getSecond());

    // TODO: Maybe use exceptions?
    assert((p1>=0 && p2>=0) && "Please don't go around making up nonexistent points");

    return Segment<int>(p1, p2);
}




