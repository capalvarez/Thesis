#include <veamy/models/constraints/EssentialConstraints.h>

EssentialConstraints::EssentialConstraints() {}

Eigen::VectorXd EssentialConstraints::getBoundaryValues(std::vector<Point> points, VeamyList<DOF> dofs) {
    Eigen::VectorXd values;
    values = Eigen::VectorXd::Zero(constrained_dofs.size());

    for (int i = 0; i < constrained_dofs.size(); ++i){
        Constraint constraintI = constraints_map[constrained_dofs.get(i)];
        DOF dofI = dofs.get(constrained_dofs.get(i));

        values(i) = constraintI.getValue(points[dofI.pointIndex()]);
    }

    return values;
}



