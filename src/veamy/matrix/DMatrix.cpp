#include "DMatrix.h"

DMatrix::DMatrix(std::vector<DOF*> dofs, Polygon p, BasePolinomials b, std::vector<Point> points) {
    this->D = Eigen::MatrixXf::Zero(dofs.size(), b.nOfPolinomials());
    this->D.col(0).setOnes();

    for(int dof_id=0; dof_id<dofs.size(); dof_id++){
        for(int poly_id=1; poly_id<b.nOfPolinomials(); poly_id++){
            Pair<int> coefficients = b.getPolinomial(poly_id);

            this->D(dof_id,poly_id) = dofs[dof_id]->getValue(points, coefficients, p);
        }
    }
}

Eigen::MatrixXf DMatrix::getDMatrix() {
    return this->D;
}



