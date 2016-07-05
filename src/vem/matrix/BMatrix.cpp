#include "BMatrix.h"

BMatrix::BMatrix(Polygon p, int k, std::vector<Point> points) {
    DegreesOfFreedom d (p,k,points);
    BasePolinomials b (k);

    this->B = Eigen::MatrixXf::Zero(b.nOfPolinomials(), d.numberOfDOF());

    if(k==1){
        this->B.row(0).setOnes();
        this->B.row(0) = this->B.row(0)*p.numberOfSides();
    }else{

    }

    std::vector<int> index = p.getPoints();

    for(int poly_id=1;poly_id<b.nOfPolinomials();poly_id++){
        std::pair<int,int> poly = b.getPolinomial(poly_id);

        for(int dof_id=0;dof_id<d.numberOfDOF();dof_id++){
            Point vertex = points[index[dof_id]];

            this->B(poly_id,dof_id) = -laplacian(poly,p,vertex) + dot(gradient(poly,p,vertex), d.normal(dof_id,points));
       }
    }

}

Eigen::MatrixXf BMatrix::getBMatrix() {
    return this->B;
}


std::pair<double, double> BMatrix::gradient(std::pair<int, int> polinomial, Polygon p, Point point) {
    double xFactor = (point.getX()-p.getCentroid().getX())/p.getDiameter();
    double yFactor = (point.getY()-p.getCentroid().getY())/p.getDiameter();

    return std::pair<double, double>(
            std::make_pair((polinomial.first)*pow(xFactor, polinomial.first-1)*pow(yFactor,polinomial.second) ,
                           (polinomial.second)*pow(xFactor,polinomial.first) *pow(yFactor, polinomial.second-1)));
}

double BMatrix::laplacian(std::pair<int, int> polinomial, Polygon p, Point point) {
    double xFactor = (point.getX()-p.getCentroid().getX())/p.getDiameter();
    double yFactor = (point.getY()-p.getCentroid().getY())/p.getDiameter();

    return (polinomial.first)*(polinomial.first-1)*pow(xFactor, polinomial.first-2)*pow(yFactor,polinomial.second) +
           (polinomial.second)*(polinomial.second-1)*pow(xFactor,polinomial.first) *pow(yFactor, polinomial.second-2);
}


double BMatrix::dot(std::pair<double, double> v1, std::pair<double, double> v2) {
    return v1.first*v2.first + v1.second*v2.second;
}


