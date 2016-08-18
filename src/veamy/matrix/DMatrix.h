#ifndef THESIS_DMATRIX_H
#define THESIS_DMATRIX_H

#include "lib/Eigen/Dense"
#include <x-poly/models/polygon/Polygon.h>
#include "matrix/dof/DegreesOfFreedom.h"
#include "BasePolinomials.h"

class DMatrix {
private:
    Eigen::MatrixXf D;
public:
    DMatrix(Polygon p, int k, std::vector<Point> points);
    Eigen::MatrixXf getDMatrix();
};


#endif
