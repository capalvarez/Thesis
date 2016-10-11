#ifndef THESIS_NATURALCONSTRAINTS_H
#define THESIS_NATURALCONSTRAINTS_H

#include <x-poly/models/polygon/Polygon.h>
#include <veamy/utilities/operations.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/constraints/Constraints.h>

class NaturalConstraints : public Constraints{
public:
    NaturalConstraints();
    double lineIntegral(std::vector<Point> points, Polygon p, int point, int DOF_index);
};


#endif
