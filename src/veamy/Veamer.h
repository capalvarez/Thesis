#ifndef THESIS_VEAMER_H
#define THESIS_VEAMER_H

#include <models/Element.h>
#include <x-poly/models/Mesh.h>
#include <x-poly/utilities/List.h>
#include <matrix/dof/OuterDOF.h>
#include <matrix/dof/DOFS.h>

typedef double(*func_t)(double, double);

class Veamer {
private:
    std::vector<Element> elements;
    List<Point> points;


    int k;
public:
    DOFS outerDOFs;
    Veamer(int k);
    void loadData(Mesh m, func_t f);
    Eigen::MatrixXd simulate();

    std::vector<Element> getElements();

};


#endif
