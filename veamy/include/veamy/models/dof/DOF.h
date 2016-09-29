#ifndef THESIS_DEGREEOFFREEDOOM_H
#define THESIS_DEGREEOFFREEDOOM_H

#include <veamy/utilities/Pair.h>
#include <x-poly/models/polygon/Polygon.h>

class DOF {
public:
    enum Axis {x, y};

    virtual double getValue(std::vector<Point> points, Pair<int> coeffs, Polygon p) = 0;
    virtual double lineIntegral(int local_id, std::vector<int> elementDOFS, std::vector<DOF*> globalDOFS, int k, Polygon p, std::vector<double> weights, std::vector<Point> points, Pair<int> poly) = 0;
    virtual double laplacianIntegral(Pair<int> poly, Polygon p) = 0;
    virtual int globalIndex() = 0;
    virtual int pointIndex() = 0;
protected:
    int index;
    DOF::Axis d;
};


#endif
