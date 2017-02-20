#include <veamy/lib/Eigen/Dense>
#include <iostream>
#include <veamy/Veamer.h>

Veamer::Veamer() {}

void Veamer::initProblem(PolygonalMesh m, ProblemConditions conditions) {
    std::vector<Point> meshPoints = m.getPoints().getList();
    this->points.push_list(meshPoints);
    this->conditions = conditions;

    std::vector<Polygon> polygons = m.getPolygons();

    for(int i=0;i<polygons.size();i++){
        createElement(polygons[i]);
    }
}

void Veamer::createElement(Polygon p) {
    polygon_to_element.insert(std::make_pair(p,elements.size()));
    elements.push_back(Element(this->conditions, p, this->points, DOFs));
}

Eigen::VectorXd Veamer::simulate() {
    Eigen::MatrixXd K;
    Eigen::VectorXd f;
    int n = this->DOFs.size();

    K = Eigen::MatrixXd::Zero(n,n);
    f = Eigen::VectorXd::Zero(n);

    for(int i=0;i<elements.size();i++){
        elements[i].assemble(DOFs, K, f);
    }

    //Apply constrained_points
    EssentialConstraints essential = this->conditions.constraints.getEssentialConstraints();
    std::vector<int> c = essential.getConstrainedDOF();

    Eigen::VectorXd boundary_values = essential.getBoundaryValues(this->points.getList(), this->DOFs.getDOFS());

    for (int j = 0; j < c.size(); ++j) {
        for (int i = 0; i < K.rows(); ++i) {
            f(i) = f(i) - (K(i,c[j])*boundary_values(j));

            K(c[j],i) = 0;
            K(i,c[j]) = 0;
        }

        K(c[j], c[j]) = 1;
        f(c[j]) = boundary_values(j);
    }

     //Solve the system
    //Eigen::VectorXd x = K.colPivHouseholderQr().solve(f);
    Eigen::VectorXd x = K.inverse()*f;

    return x;
}

void Veamer::replaceElement(Polygon old, std::vector<Polygon> newPolygons) {
    int to_remove = polygon_to_element[old];
    polygon_to_element.erase(old);

    elements.erase(elements.begin() + to_remove);

    for (int i = 0; i < newPolygons.size(); ++i) {
        createElement(newPolygons[i]);
    }
}

void Veamer::replaceElements(std::vector<Polygon> old, std::vector<Polygon> newPolygons, UniqueList<Point> points) {
    this->points = points;

    for (int i = 0; i < old.size(); ++i) {
        int to_remove = polygon_to_element[old[i]];
        polygon_to_element.erase(old[i]);

        elements.erase(elements.begin() + to_remove);
    }

    for (int i = 0; i < newPolygons.size(); ++i) {
        createElement(newPolygons[i]);
    }
}

Pair<int> Veamer::pointToDOFS(int point_index) {
    return this->DOFs.pointToDOFS(point_index);
}

Material Veamer::getMaterial() {
    return conditions.material;
}

UniqueList<Point> Veamer::getPoints() {
    return this->points;
}

