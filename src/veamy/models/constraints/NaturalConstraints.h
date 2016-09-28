#ifndef THESIS_NATURALCONSTRAINTS_H
#define THESIS_NATURALCONSTRAINTS_H

#include "Constraints.h"

class NaturalConstraints : public Constraints{
public:
    NaturalConstraints();
    double lineIntegral(std::vector<Point> points, Polygon p, int DOF_index, int local_index, int k, Eigen::MatrixXd PiZS);
};


#endif
