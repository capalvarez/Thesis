#ifndef THESIS_DMATRIX_H
#define THESIS_DMATRIX_H

#include "lib/Eigen/Dense"
#include <x-poly/models/polygon/Polygon.h>
#include "BasePolinomials.h"
#include <matrix/dof/DOF.h>

class DMatrix {
private:
    Eigen::MatrixXf D;
public:
    DMatrix(std::vector<DOF*> dofs, Polygon p, BasePolinomials b, std::vector<Point> points);
    Eigen::MatrixXf getDMatrix();
};


#endif
