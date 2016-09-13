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

class Veamer {
private:
    Constraints constraints;
    std::vector<Element> elements;
    List<Point> points;

    int k;
public:
    DOFS DOFs;
    Veamer(int k);

    void loadGeometry(Mesh m, Constraints constraints, func_t f);
    Eigen::VectorXd simulate();
    std::vector<Element> getElements();

};


#endif
