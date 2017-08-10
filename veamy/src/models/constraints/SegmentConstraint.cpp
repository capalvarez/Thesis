#include <veamy/models/constraints/SegmentConstraint.h>

SegmentConstraint::SegmentConstraint() : Constraint() {}

SegmentConstraint::SegmentConstraint(IndexSegment s, Constraint::Direction d, ConstraintValue *value) : Constraint(d, value) {
    this->constraints.push_back(s);
}

SegmentConstraint::SegmentConstraint(std::vector<IndexSegment> s, Constraint::Direction d, ConstraintValue *value)
        : Constraint(d, value) {
    this->constraints.push_list(s);
}

SegmentConstraint::SegmentConstraint(PointSegment s, std::vector<Point> points, Constraint::Direction d,
                                     ConstraintValue *value) : Constraint(d, value) {
    IndexSegment int_segment = fromPointToInt(s, points);
    this->constraints.push_back(int_segment);
}

SegmentConstraint::SegmentConstraint(PointSegment s, UniqueList<Point> points, Constraint::Direction d,
                                     ConstraintValue *value) : Constraint(d, value) {
    IndexSegment int_segment = fromPointToInt(s, points.getList());
    this->constraints.push_back(int_segment);
}

SegmentConstraint::SegmentConstraint(std::vector<PointSegment> s, std::vector<Point> points, Constraint::Direction d,
                                     ConstraintValue *value) : Constraint(d, value) {
    for(int i = 0; i<s.size(); i++){
        IndexSegment int_segment = fromPointToInt(s[i], points);
        this->constraints.push_back(int_segment);
    }
}

SegmentConstraint::SegmentConstraint(std::vector<PointSegment> s, UniqueList<Point> points, Constraint::Direction d,
                                     ConstraintValue *value) : Constraint(d, value) {
    for(int i = 0; i<s.size(); i++){
        IndexSegment int_segment = fromPointToInt(s[i], points.getList());
        this->constraints.push_back(int_segment);
    }
}

UniqueList<IndexSegment> SegmentConstraint::getSegments() {
    return this->constraints;
}

IndexSegment SegmentConstraint::fromPointToInt(PointSegment s, std::vector<Point> points) {
    int p1 = utilities::indexOf(points, s.getFirst());
    int p2 = utilities::indexOf(points, s.getSecond());

    if(p1<0 || p2<0){
        throw std::invalid_argument("Please don't go around making up nonexistent points");
    }

    return IndexSegment(p1, p2);
}
