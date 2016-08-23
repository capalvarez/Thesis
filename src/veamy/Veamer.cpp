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

void Veamer::simulate() {
    Eigen::MatrixXf K;

    for(int i=0;i<elements.size();i++){

    }

}

std::vector<Element> Veamer::getElements() {
    return this->elements;
}



