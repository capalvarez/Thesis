#ifndef THESIS_VEAMER_H
#define THESIS_VEAMER_H

#include <x-poly/models/Mesh.h>
#include <x-poly/utilities/List.h>
#include <veamy/models/dof/DOFS.h>
#include <veamy/models/constraints/EssentialConstraints.h>
#include <include/veamy/utilities/matrixOps.h>
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

    std::vector<Element> elements;
    std::unordered_map<Polygon, int, PolygonHasher> polygon_to_element;
    List<Point> points;

    void createElement(Polygon p);
public:
    DOFS DOFs;
    Veamer();

    void initProblem(Mesh m, ProblemConditions conditions);
    Eigen::VectorXd simulate();

    void replaceElement(Polygon old, std::vector<Polygon> newPolygons);
    void replaceElements(std::vector<Polygon> old, std::vector<Polygon> newPolygons, List<Point> points);

    Pair<int> pointToDOFS(int point_index);
    Material getMaterial();
    List<Point> getPoints();
};


#endif
