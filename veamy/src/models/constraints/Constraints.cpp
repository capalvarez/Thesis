#include <veamy/models/constraints/Constraints.h>

void Constraints::addConstraint(Constraint c) {
    UniqueList<Segment<int>> segments = c.getSegments();

    for (int i = 0; i < segments.size(); ++i) {
        constrained_segments.push_back(segments.get(i));
        segment_map.insert(std::make_pair(segments.get(i), c));
    }
}

isConstrainedInfo Constraints::isConstrained(std::vector<Point> points, Segment<int> s) {
   // TODO: Some data structure is necessary to optimize this, is slow as a snail

    for (int i = 0; i < constrained_segments.size(); ++i) {
        if(constrained_segments[i].contains(points, s))
            return isConstrainedInfo(constrained_segments[i]);
    }

    return isConstrainedInfo();
}

bool Constraints::isConstrained(int dof) {
    return constrained_dofs.contains(dof);
}

std::vector<int> Constraints::getConstrainedDOF() {
    return constrained_dofs.getList();
}

void Constraints::addConstrainedDOF(std::vector<Point> points, int DOF_index, DOF::Axis axis, SegmentPair<int> pair) {
    addConstrainedDOFBySegment(points, DOF_index, axis, pair.s1);

    if(pair.number!=1){
        addConstrainedDOFBySegment(points, DOF_index, axis, pair.s2);
    }
}

void Constraints::addConstrainedDOFBySegment(std::vector<Point> points, int DOF_index, DOF::Axis axis, Segment<int> s) {
    isConstrainedInfo info = isConstrained(points, s);

    if(info.isConstrained){
        Constraint constraint = segment_map[info.container];
        Constraint::Direction direction = constraint.getDirection();

        bool insert;

        switch(direction){
            case(Constraint::Direction::Vertical):
                insert = axis==DOF::Axis::y;
                break;
            case (Constraint::Direction::Horizontal):
                insert = axis==DOF::Axis::x;
                break;
            default:
                insert = true;
        }

        if(insert){
            constrained_dofs.push_back(DOF_index);
            constraints_map.insert(std::pair<int,Constraint>(DOF_index, constraint));
        }
    }

}

