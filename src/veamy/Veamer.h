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
    //TODO: Check for inconsistencies (cannot have natural and essential conditions on the same segments)
    EssentialConstraints essential;
    NaturalConstraints natural;
    std::vector<Element> elements;
    List<Point> points;

    int k;
public:
    DOFS DOFs;
    Veamer(int k);

    void loadGeometry(Mesh m, EssentialConstraints constraints, NaturalConstraints natural, BodyForce* f);
    Eigen::VectorXd simulate();
    std::vector<Element> getElements();

};


#endif
