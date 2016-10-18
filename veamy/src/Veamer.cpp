#include <veamy/lib/Eigen/Dense>
#include <iostream>
#include <veamy/Veamer.h>

Veamer::Veamer() {}

void Veamer::loadGeometry(Mesh m, ConstraintsContainer c, BodyForce* f) {
    std::vector<Point> meshPoints = m.getPoints();
    this->points.push_list(meshPoints);
    this->constraints = c;

    std::vector<Polygon> polygons = m.getPolygons();

    for(int i=0;i<polygons.size();i++){
        createElement(polygons[i], f);
    }
}

void Veamer::createElement(Polygon p, BodyForce* f) {
    polygon_to_element.insert(std::make_pair(p,elements.size()));
    elements.push_back(Element(this->constraints, p, this->points, DOFs, f));
}


Eigen::VectorXd Veamer::simulate() {
    Eigen::MatrixXd K;
    Eigen::VectorXd f;
    int n = this->DOFs.size();

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

    // std::cout << boundary_values <<  std::endl << std::endl << K_b << std::endl << std::endl;

    for (int i = 0; i < K.rows(); ++i) {
        f(i) = f(i) - (K_b.row(i)*boundary_values);
    }


    for (int j = 0; j < c.size(); ++j) {
        K.row(c[j]).setZero();
        K.col(c[j]).setZero();
        K(c[j], c[j]) = 1;

        f(c[j]) = boundary_values(j);
    }

    //std::cout << K << std::endl << std::endl << f << std::endl << std::endl;

    //Solve the system
    Eigen::VectorXd x = K.inverse()*f;

    return x;
}

std::vector<Element> Veamer::getElements() {
    return this->elements;
}

void Veamer::replaceElement(Polygon old, std::vector<Polygon> newPolygons) {
    int to_remove = polygon_to_element[old];
    polygon_to_element.erase(old);

    elements.erase(elements.begin() + to_remove, elements.end());

    for (int i = 0; i < newPolygons.size(); ++i) {
        createElement(newPolygons[i]);
    }
}



