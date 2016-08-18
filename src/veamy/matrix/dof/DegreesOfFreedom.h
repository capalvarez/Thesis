#ifndef THESIS_DEGREESOFFREEDOM_H
#define THESIS_DEGREESOFFREEDOM_H

#include <vector>
#include <x-poly/models/basic/Point.h>
#include <x-poly/models/polygon/Polygon.h>
#include "utilities/Pair.h"
#include <veamy/matrix/lobattoQuadrature.h>

class DegreesOfFreedom {
private:
    int order;
    int numberOfSides;

    std::vector<int> dof;
public:
    DegreesOfFreedom(Polygon p, int k, std::vector<Point>& points);
    int numberOfDOF();
    std::vector<int> getNeighbours(int dof);

    std::vector<int> getDOF();
};


#endif