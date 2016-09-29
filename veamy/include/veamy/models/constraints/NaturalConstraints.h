#ifndef THESIS_NATURALCONSTRAINTS_H
#define THESIS_NATURALCONSTRAINTS_H

#include <veamy/matrix/lobattoQuadrature.h>
#include <x-poly/models/polygon/Polygon.h>
#include <veamy/matrix/BasePolinomials.h>
#include <veamy/utilities/operations.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/constraints/Constraints.h>

class NaturalConstraints : public Constraints{
public:
    NaturalConstraints();
    double lineIntegral(std::vector<Point> points, Polygon p, int DOF_index, int local_index, int k, Eigen::MatrixXd PiZS);
};


#endif
