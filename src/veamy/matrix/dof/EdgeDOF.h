#ifndef THESIS_EDGEDOF_H
#define THESIS_EDGEDOF_H


#include "OuterDOF.h"

class EdgeDOF : public OuterDOF{
public:
    EdgeDOF(int i);
    double lineIntegral(int local_id, int k, Polygon p, std::vector<double> weights, std::vector<Point> points, Pair<int> poly);
};


#endif
