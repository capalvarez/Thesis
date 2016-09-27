#include <Eigen/Dense>
#include <iostream>
#include "Veamer.h"


Veamer::Veamer(int k) {
    this->k = k;
}

Veamer(){}

void Veamer::loadGeometry(Mesh m, Constraints constraints, func_t f) {
    //TODO: Optimize space and use a map (polygon_index, element_index)
    std::vector<Point> meshPoints = m.getPoints();
    this->points.push_list(meshPoints);
    this->constraints = constraints;
    this->f = f;

    std::vector<Polygon> polygons = m.getElements();

    for(int i=0;i<polygons.size();i++){
        createElement(polygons[i]);
    }
}

void Veamer::createElement(Polygon p) {
    polygon_to_element.insert(std::make_pair(p,elements.size()));
    elements.push_back(Element(this->constraints, p, this->points, DOFs, k, f));
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
    std::vector<int> c = this->constraints.getConstrainedDOF();

    Eigen::MatrixXd K_b;
    K_b= matrixOps::getColumns(K, c);

    Eigen::VectorXd boundary_values = this->constraints.getBoundaryValues(this->points.getList(), this->DOFs.getDOFS());


    for (int i = 0; i < K.rows(); ++i) {
        f(i) = f(i) - (K_b.row(i)*boundary_values);
    }

    for (int j = 0; j < c.size(); ++j) {
        matrixOps::removeRow(K, c[j]);
        matrixOps::removeColumn(K, c[j]);

        matrixOps::removeElement(f,c[j]);
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

void Veamer::replaceElement(Polygon old, std::vector<Polygon> newPolygons) {
    int to_remove = polygon_to_element[old];
    polygon_to_element.erase(old);

    elements.erase(std::remove(elements.begin(), elements.end(), to_remove), elements.end());

    for (int i = 0; i < newPolygons.size(); ++i) {
        createElement(newPolygons[i]);
    }
}




