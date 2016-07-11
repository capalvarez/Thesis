#include <utilities/operations.h>
#include "BMatrix.h"

BMatrix::BMatrix(Polygon p, int k, std::vector<Point>& points) {
     DegreesOfFreedom d (p,k,points);
    BasePolinomials b (k);

    this->B = Eigen::MatrixXf::Zero(b.nOfPolinomials(), d.numberOfDOF());

    if(k==1){
        this->B.row(0).setOnes();
        this->B.row(0) = this->B.row(0)*p.numberOfSides();
    }else{

    }

    std::vector<int> dof = d.getDOF();

    for(int poly_id=1;poly_id<b.nOfPolinomials();poly_id++){
        Pair<int> poly = b.getPolinomial(poly_id);

        for(int dof_id=0;dof_id<d.numberOfDOF();dof_id++){
            Point vertex = points[dof[dof_id]];

            double lap = -operations::laplacian(poly,p,vertex);
            double grad = operations::gradient(poly,p,vertex).dot(d.normal(dof_id,points));

            double result =  lap + grad;
            this->B(poly_id,dof_id) = result;
       }
    }

}

Eigen::MatrixXf BMatrix::getBMatrix() {
    return this->B;
}




