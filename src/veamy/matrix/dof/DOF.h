#ifndef THESIS_DEGREEOFFREEDOOM_H
#define THESIS_DEGREEOFFREEDOOM_H

#include <veamy/utilities/Pair.h>
#include <x-poly/models/polygon/Polygon.h>
#include <veamy/utilities/Pair.h>

class DOF {
public:
    virtual double getValue(std::vector<Point> points, Pair<int> coeffs, Polygon p) = 0;
    virtual double lineIntegral(int local_id, int k, Polygon p, std::vector<double> weights, std::vector<Point> points, Pair<int> poly) = 0;
    virtual double laplacianIntegral(Pair<int> poly, Polygon p) = 0;
};


#endif
