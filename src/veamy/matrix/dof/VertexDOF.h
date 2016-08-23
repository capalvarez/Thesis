#ifndef THESIS_VERTEXDOF_H
#define THESIS_VERTEXDOF_H


#include "OuterDOF.h"

class VertexDOF : public OuterDOF{
public:
    VertexDOF(int i);
    double lineIntegral(int local_id, int k, Polygon p, std::vector<double> weights, std::vector<Point> points, Pair<int> poly);
};


#endif
