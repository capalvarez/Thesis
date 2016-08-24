#ifndef THESIS_VEAMER_H
#define THESIS_VEAMER_H

#include <models/Element.h>
#include <x-poly/models/Mesh.h>
#include <x-poly/utilities/List.h>
#include <matrix/dof/OuterDOF.h>
#include <matrix/dof/OuterDOFS.h>

class Veamer {
private:
    std::vector<Element> elements;
    List<Point> points;
    OuterDOFS outerDOFs;

    int k;
public:
    Veamer(int k);
    void loadData(Mesh m);
    Eigen::MatrixXd simulate();

    std::vector<Element> getElements();

};


#endif
