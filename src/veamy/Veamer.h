#ifndef THESIS_VEAMER_H
#define THESIS_VEAMER_H

#include <models/Element.h>
#include <x-poly/models/Mesh.h>
#include <x-poly/utilities/List.h>
#include <models/dof/OuterDOF.h>
#include <models/dof/DOFS.h>
#include <models/constraints/EssentialConstraints.h>
#include <matrix/matrixOps.h>
#include <physics/BodyForce.h>

class Veamer {
private:
    EssentialConstraints constraints;
    std::vector<Element> elements;
    List<Point> points;

    int k;
public:
    DOFS DOFs;
    Veamer(int k);

    void loadGeometry(Mesh m, EssentialConstraints constraints, BodyForce* f);
    Eigen::VectorXd simulate();
    std::vector<Element> getElements();

};


#endif
