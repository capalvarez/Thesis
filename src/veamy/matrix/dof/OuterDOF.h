#ifndef THESIS_OUTERDOF_H
#define THESIS_OUTERDOF_H

#include <x-poly/models/polygon/Polygon.h>
#include <veamy/utilities/Pair.h>
#include "DOF.h"

class OuterDOF : public DOF {
protected:
    int index;
public:
    OuterDOF(int i);

    double getValue(std::vector<Point> points, Pair<int> coeffs, Polygon p);
    virtual double lineIntegral(int local_id, int k, Polygon p, std::vector<double> weights, std::vector<Point> points, Pair<int> poly) = 0;
    double laplacianIntegral(Pair<int> poly, Polygon p);
    int globalIndex();
};


#endif
