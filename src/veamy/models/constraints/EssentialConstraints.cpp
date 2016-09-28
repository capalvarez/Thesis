#include "EssentialConstraints.h"

EssentialConstraints::EssentialConstraints() {}

std::vector<int> EssentialConstraints::getConstrainedDOF() {
    return constrained_dofs.getList();
}

void EssentialConstraints::addConstrainedDOF(int DOF_index, DOF::Axis axis, SegmentPair pair) {
    addConstrainedDOFBySegment(DOF_index, axis, pair.s1);

    if(pair.number!=1){
        addConstrainedDOFBySegment(DOF_index, axis, pair.s2);
    }

}

void EssentialConstraints::addConstrainedDOFBySegment(int DOF_index, DOF::Axis axis, Segment s) {
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


Eigen::VectorXd EssentialConstraints::getBoundaryValues(std::vector<Point> points, List<DOF*> dofs) {
    Eigen::VectorXd values;
    values = Eigen::VectorXd::Zero(constrained_dofs.size());

    for (int i = 0; i < constrained_dofs.size(); ++i){
        Constraint constraintI = constraints_map[constrained_dofs.get(i)];
        DOF* dofI = dofs.get(constrained_dofs.get(i));

        values(i) = constraintI.getValue(points[dofI->pointIndex()]);
    }

    return values;
}



