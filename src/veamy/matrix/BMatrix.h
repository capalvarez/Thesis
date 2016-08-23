#ifndef THESIS_BMATRIX_H
#define THESIS_BMATRIX_H

#include "lib/Eigen/Dense"
#include <x-poly/models/polygon/Polygon.h>
#include <x-poly/models/basic/Point.h>
#include <matrix/dof/DOF.h>
#include "BasePolinomials.h"

class BMatrix {
private:
    Eigen::MatrixXd B;
public:
    BMatrix(int k, std::vector<DOF*> dofs, Polygon p, BasePolinomials b, std::vector<Point>& points);
    Eigen::MatrixXd getBMatrix();

};


#endif