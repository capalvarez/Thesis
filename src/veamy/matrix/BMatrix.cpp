#include <utilities/operations.h>
#include "BMatrix.h"
#include <veamy/models/Edge.h>
#include "lobattoQuadrature.h"

BMatrix::BMatrix(int k, std::vector<DOF*> dofs, Polygon p, BasePolinomials b, std::vector<Point>& points) {
    this->B = Eigen::MatrixXd::Zero(b.nOfPolinomials(), dofs.size());

    if(k==1){
        this->B.row(0).setOnes();
        this->B.row(0) = this->B.row(0)*(1/(double)p.numberOfSides());
    }else{
        this->B(0,dofs.size()-1) = 1;
    }

    std::vector<double> weight;
    std::vector<double> quadrature_points;
    lobatto::lobatto_set(k+1,quadrature_points,weight);

    for(int poly_id=1;poly_id<b.nOfPolinomials();poly_id++){
        Pair<int> poly = b.getPolinomial(poly_id);

        for(int dof_id=0;dof_id<dofs.size();dof_id++){
            this->B(poly_id,dof_id) = dofs[dof_id]->lineIntegral(dof_id,k,p,weight,points,poly) +
                    dofs[dof_id]->laplacianIntegral(poly,p);
       }
    }
}

Eigen::MatrixXd BMatrix::getBMatrix() {
    return this->B;
}







