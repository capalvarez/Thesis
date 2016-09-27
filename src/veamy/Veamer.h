#ifndef THESIS_VEAMER_H
#define THESIS_VEAMER_H

#include <models/Element.h>
#include <x-poly/models/Mesh.h>
#include <x-poly/utilities/List.h>
#include <models/dof/OuterDOF.h>
#include <models/dof/DOFS.h>
#include <models/constraints/Constraints.h>
#include <matrix/matrixOps.h>

typedef double(*func_t)(double, double);

struct PolygonHasher {
    std::size_t operator()(const Polygon &k) const {
        using std::size_t;
        using std::hash;

        return k.hash;
    }
};

class Veamer {
private:
    int k;

    func_t f;
    Constraints constraints;

    std::unordered_map<Polygon, int, PolygonHasher> polygon_to_element;
    std::vector<Element> elements;
    List<Point> points;

    void createElement(Polygon p);
public:
    DOFS DOFs;
    Veamer(int k);
    Veamer();

    void loadGeometry(Mesh m, Constraints constraints, func_t f);
    Eigen::VectorXd simulate();
    std::vector<Element> getElements();

    void replaceElement(Polygon old, std::vector<Polygon> newPolygons);

};


#endif
