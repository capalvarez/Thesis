#include <veamy/lib/Eigen/Dense>
#include <iostream>
#include <veamy/Veamer.h>

Veamer::Veamer(int k) {
    this->k = k;
}

void Veamer::loadGeometry(Mesh m, ConstraintsContainer c, BodyForce* f) {
    //TODO: Make a constructor that doesnt receive body forces (or several)

    std::vector<Point> meshPoints = m.getPoints();
    this->points.push_list(meshPoints);
    this->constraints = c;

    std::vector<Polygon> polygons = m.getElements();

    for(int i=0;i<polygons.size();i++){
        elements.push_back(Element(this->constraints, polygons[i], this->points, DOFs, k, f));
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

    //Apply constrained_points
    EssentialConstraints essential = this->constraints.getEssentialConstraints();
    std::vector<int> c = essential.getConstrainedDOF();

    Eigen::MatrixXd K_b;
    K_b= matrixOps::getColumns(K, c);

    Eigen::VectorXd boundary_values = essential.getBoundaryValues(this->points.getList(), this->DOFs.getDOFS());

    for (int i = 0; i < K.rows(); ++i) {
        f(i) = f(i) - (K_b.row(i)*boundary_values);
    }

    for (int j = 0; j < c.size(); ++j) {
        matrixOps::removeRow(K, c[j]);
        matrixOps::removeColumn(K, c[j]);

        matrixOps::removeElement(f,c[c.size() - 1 - j]);
    }

    //Solve the system
    Eigen::VectorXd x = K.colPivHouseholderQr().solve(f);

    int cIndex = 0;
    int xIndex = 0;
    Eigen::VectorXd xF;
    xF = Eigen::VectorXd::Zero(c.size() + x.rows());

    for (int i = 0; i < xF.rows(); ++i) {
        if(i==c[cIndex]){
            xF(i) = boundary_values(cIndex);
            cIndex++;
        } else{
            xF(i) = x(xIndex);
            xIndex++;
        }
    }

    return xF;
}

std::vector<Element> Veamer::getElements() {
    return this->elements;
}



