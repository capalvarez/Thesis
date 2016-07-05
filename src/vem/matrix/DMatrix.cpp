#include "DMatrix.h"

DMatrix::DMatrix(Polygon p, int k, std::vector<Point> points) {
    DegreesOfFreedom d (p,k,points);
    BasePolinomials b (k);

    this->D = Eigen::MatrixXf::Zero(d.numberOfDOF(), b.nOfPolinomials());
    this->D.col(0).setOnes();

    Point centroid = p.getCentroid();
    double diameter = p.getDiameter();
    std::vector<int> index = p.getPoints();

    for(int dof_id=0; dof_id<d.numberOfDOF(); dof_id++){
        Point vertex = points[index[dof_id]];
        double xPol = (vertex.getX()-centroid.getX())/diameter;
        double yPol = (vertex.getY()-centroid.getY())/diameter;

        for(int poly_id=1; poly_id<b.nOfPolinomials(); poly_id++){
            std::pair<int,int> coefficients = b.getPolinomial(poly_id);

            this->D(dof_id,poly_id) = pow(xPol, coefficients.first)* pow(yPol,coefficients.second);
        }
    }
}

Eigen::MatrixXf DMatrix::getDMatrix() {
    return this->D;
}



