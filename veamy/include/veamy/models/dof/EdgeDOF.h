#ifndef THESIS_EDGEDOF_H
#define THESIS_EDGEDOF_H

#include "OuterDOF.h"
#include <veamy/models/Edge.h>
#include <veamy/utilities/operations.h>

class EdgeDOF : public OuterDOF{
public:
    EdgeDOF(int i, int p, Axis axis);
    double lineIntegral(int local_id, std::vector<int> elementDOFS, std::vector<DOF*> globalDOFS, int k, Polygon p, std::vector<double> weights, std::vector<Point> points, Pair<int> poly);
};


#endif
