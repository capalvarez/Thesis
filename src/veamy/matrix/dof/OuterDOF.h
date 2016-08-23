#ifndef THESIS_OUTERDOF_H
#define THESIS_OUTERDOF_H

#include <x-poly/models/polygon/Polygon.h>
#include <utilities/Pair.h>
#include "DOF.h"

class OuterDOF : public DOF {
protected:
    int index;
public:
    OuterDOF(int i);

    double getValue(std::vector<Point> points, Pair<int> coeffs, Polygon p);
    virtual double lineIntegral(int k, Polygon p, std::vector<double> weights, std::vector<Point> points, Pair<int> poly) = 0;
    double laplacianIntegral(Pair<int> poly, Polygon p);
};


#endif
