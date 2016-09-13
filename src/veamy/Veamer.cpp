#include <Eigen/Dense>
#include <iostream>
#include "Veamer.h"


Veamer::Veamer(int k) {
    this->k = k;
}

void Veamer::loadGeometry(Mesh m, Constraints constraints, func_t f) {
    std::vector<Point> meshPoints = m.getPoints();
    this->points.push_list(meshPoints);
    this->constraints = constraints;

    std::vector<Polygon> polygons = m.getElements();

    for(int i=0;i<polygons.size();i++){
        elements.push_back(Element(polygons[i], this->points, DOFs, k, f));
    }
}

Eigen::VectorXd Veamer::simulate() {
    Eigen::MatrixXd K;
    Eigen::VectorXd f;
    int n = this->DOFs.size() + (this->k)*(this->k-1)/2;

    K = Eigen::MatrixXd::Zero(n,n);
    f = Eigen::VectorXd::Zero(n);

    for(int i=0;i<elements.size();i++){
        elements[i].assembleK(DOFs, K);
        elements[i].assembleF(DOFs, f);
    }

    //Apply constraints
    std::vector<int> c = this->constraints.getConstrainedDOF();

    for (int j = 0; j < c.size(); ++j) {

    }



    //Solve the system
    Eigen::VectorXd x = K.colPivHouseholderQr().solve(f);

    return x;
}

std::vector<Element> Veamer::getElements() {
    return this->elements;
}




