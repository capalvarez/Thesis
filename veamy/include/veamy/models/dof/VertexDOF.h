#ifndef THESIS_VERTEXDOF_H
#define THESIS_VERTEXDOF_H

#include <veamy/models/dof/OuterDOF.h>
#include <veamy/models/dof/DOFS.h>
#include <veamy/models/Edge.h>
#include <veamy/utilities/operations.h>

class DOFS;

class VertexDOF : public OuterDOF {
public:
    VertexDOF(int i, int p, Axis axis);
    double lineIntegral(int local_id, std::vector<int> elementDOFS, std::vector<DOF*> globalDOFS, int k, Polygon p, std::vector<double> weights, std::vector<Point> points, Pair<int> poly);
};


#endif
