#include <Eigen/Dense>
#include "Veamer.h"


Veamer::Veamer(int k) {
    this->k = k;
}

void Veamer::loadData(Mesh m) {
    std::vector<Point> meshPoints = m.getPoints();
    this->points.push_list(meshPoints);

    std::vector<Polygon> polygons = m.getElements();

    for(int i=0;i<polygons.size();i++){
        elements.push_back(Element(polygons[i], this->points, outerDOFs, k));
    }
}

Eigen::MatrixXd Veamer::simulate() {
    Eigen::MatrixXd K;
    int n = this->outerDOFs.size() + (this->k)*(this->k-1)/2;

    K = Eigen::MatrixXd::Zero(n,n);

    for(int i=0;i<elements.size();i++){
        elements[i].assembleK(outerDOFs, K);
    }

    return K;
}

std::vector<Element> Veamer::getElements() {
    return this->elements;
}



