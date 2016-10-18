#ifndef THESIS_VEAMER_H
#define THESIS_VEAMER_H

#include <x-poly/models/Mesh.h>
#include <x-poly/utilities/List.h>
#include <veamy/models/dof/DOFS.h>
#include <veamy/models/constraints/EssentialConstraints.h>
#include <veamy/matrix/matrixOps.h>
#include <veamy/physics/BodyForce.h>
#include <veamy/models/constraints/ConstraintsContainer.h>
#include <veamy/models/Element.h>
#include <veamy/lib/Eigen/Dense>

struct PolygonHasher {
    std::size_t operator()(const Polygon &k) const {
        using std::size_t;
        using std::hash;

        return k.hash;
    }
};

class Veamer {
private:
    //TODO: Check for inconsistencies (cannot have natural and essential conditions on the same segments)
    ConstraintsContainer constraints;
    std::vector<Element> elements;
    std::unordered_map<Polygon, int, PolygonHasher> polygon_to_element;
    List<Point> points;

    void createElement(Polygon p, BodyForce* f);
public:
    DOFS DOFs;
    Veamer();

    void loadGeometry(Mesh m, ConstraintsContainer c, BodyForce* f);
    Eigen::VectorXd simulate();
    std::vector<Element> getElements();

    void replaceElement(Polygon old, std::vector<Polygon> newPolygons);

};


#endif
