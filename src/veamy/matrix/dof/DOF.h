#ifndef THESIS_DEGREEOFFREEDOOM_H
#define THESIS_DEGREEOFFREEDOOM_H


#include <veamy/utilities/Pair.h>
#include <x-poly/models/polygon/Polygon.h>
#include <utilities/Pair.h>

class DOF {
public:
    virtual double getValue(std::vector<Point> points, Pair<int> coeffs, Polygon p) = 0;
};


#endif //THESIS_DEGREEOFFREEDOOM_H
