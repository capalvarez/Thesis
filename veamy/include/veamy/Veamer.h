#ifndef THESIS_VEAMER_H
#define THESIS_VEAMER_H

#include <x-poly/models/Mesh.h>
#include <veamy/models/dof/DOFS.h>
#include <veamy/models/constraints/EssentialConstraints.h>
#include <veamy/models/Element.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/physics/ProblemConditions.h>

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
    ProblemConditions conditions;

    std::unordered_map<Polygon, int, PolygonHasher> polygon_to_element;
    UniqueList<Point> points;

    void createElement(Polygon p);
public:
    DOFS DOFs;
    std::vector<Element> elements;
    Veamer();

    void initProblem(Mesh m, ProblemConditions conditions);
    Eigen::VectorXd simulate();

    void replaceElement(Polygon old, std::vector<Polygon> newPolygons);
    void replaceElements(std::vector<Polygon> old, std::vector<Polygon> newPolygons, UniqueList<Point> points);

    Pair<int> pointToDOFS(int point_index);
    Material getMaterial();
    UniqueList<Point> getPoints();
};


#endif
