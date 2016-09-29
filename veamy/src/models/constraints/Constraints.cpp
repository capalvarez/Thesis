#include <veamy/models/constraints/Constraints.h>

void Constraints::addConstraint(Constraint c) {
    List<Segment> segments = c.getSegments();

    for (int i = 0; i < segments.size(); ++i) {
        constrained_segments.insert(std::make_pair(segments.get(i), c));
    }
}

bool Constraints::isConstrained(Segment s) {
    return constrained_segments.find(s)!=constrained_segments.end();
}

bool Constraints::isConstrained(int dof) {
    return constrained_dofs.contains(dof);
}

std::vector<int> Constraints::getConstrainedDOF() {
    return constrained_dofs.getList();
}

void Constraints::addConstrainedDOF(int DOF_index, DOF::Axis axis, SegmentPair pair) {
    addConstrainedDOFBySegment(DOF_index, axis, pair.s1);

    if(pair.number!=1){
        addConstrainedDOFBySegment(DOF_index, axis, pair.s2);
    }
}

void Constraints::addConstrainedDOFBySegment(int DOF_index, DOF::Axis axis, Segment s) {
    //TODO: Check incompatible constrains

    if(isConstrained(s)){
        Constraint constraint = constrained_segments[s];
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

