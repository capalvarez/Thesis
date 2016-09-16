#include "Constraints.h"

Constraints::Constraints() {}

void Constraints::addConstraint(Constraint *c) {
    c->addToMap(constrained_points);
}

bool Constraints::isConstrained(Point p) {
    return constrained_points.find(p)!=constrained_points.end();
}

std::vector<int> Constraints::getConstrainedDOF() {
    return constrained_dofs.getList();
}

void Constraints::addConstrainedDOF(Point p, int DOF_index, DOF::Axis axis) {
    if(isConstrained(p)){
        Constraint* constraint = constrained_points[p];
        Constraint::Direction direction = constraint->getDirection();

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
            constraints_map.insert({DOF_index,constraint});
        }
    }
}

Eigen::VectorXd Constraints::getBoundaryValues(std::vector<Point> points, List<DOF*> dofs) {
    Eigen::VectorXd values;
    values = Eigen::VectorXd::Zero(dofs.size());

    for (int i = 0; i < constrained_dofs.size(); ++i){
        Constraint* constraintI = constraints_map[constrained_dofs.get(i)];
        DOF* dofI = dofs.get(constrained_dofs.get(i));

        values[constrained_dofs.get(i)] = constraintI->getValue(points[dofI->pointIndex()]);
    }

    return values;
}


