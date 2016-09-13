#ifndef THESIS_DEGREEOFFREEDOOM_H
#define THESIS_DEGREEOFFREEDOOM_H

#include <veamy/utilities/Pair.h>
#include <x-poly/models/polygon/Polygon.h>
#include <veamy/utilities/Pair.h>
#include "DOFS.h"

class DOFS;

class DOF {
protected:
    int index;
    Axis d;
public:
    enum Axis {x, y};

    virtual double getValue(std::vector<Point> points, Pair<int> coeffs, Polygon p) = 0;
    virtual double lineIntegral(int local_id, std::vector<int> elementDOFS, DOFS globalDOFS, int k, Polygon p, std::vector<double> weights, std::vector<Point> points, Pair<int> poly) = 0;
    virtual double laplacianIntegral(Pair<int> poly, Polygon p) = 0;
    virtual int globalIndex() = 0;
    virtual int pointIndex() = 0;
};


#endif
