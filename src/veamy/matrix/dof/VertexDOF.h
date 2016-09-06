#ifndef THESIS_VERTEXDOF_H
#define THESIS_VERTEXDOF_H


#include "OuterDOF.h"

class VertexDOF : public OuterDOF{
public:
    VertexDOF(int i, int p);
    double lineIntegral(int local_id, std::vector<int> elementDOFS, DOFS globalDOFS, int k, Polygon p, std::vector<double> weights, std::vector<Point> points, Pair<int> poly);
};


#endif
