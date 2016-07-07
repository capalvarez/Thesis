#ifndef THESIS_BMATRIX_H
#define THESIS_BMATRIX_H

#include "lib/Eigen/Dense"
#include <models/polygon/Polygon.h>
#include "DegreesOfFreedom.h"
#include "BasePolinomials.h"

class BMatrix {
private:
    Eigen::MatrixXf B;
public:
    BMatrix(Polygon p, int k, std::vector<Point> points);
    Eigen::MatrixXf getBMatrix();

};


#endif