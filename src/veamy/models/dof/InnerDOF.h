#ifndef THESIS_INNERDOF_H
#define THESIS_INNERDOF_H

#include <matrix/integration/IntegrationPolygon.h>
#include <utilities/operations.h>
#include "DOF.h"
#include <veamy/matrix/integration/functions/MaMbFunction.h>

class InnerDOF : public DOF{
private:
    Pair<int> alpha;
public:
    InnerDOF(Pair<int> a, int index, Axis axis);

    double getValue(std::vector<Point> points, Pair<int> coeffs, Polygon p);
    double lineIntegral(int local_id, std::vector<int> elementDOFS, DOFS globalDOFS, int k, Polygon p, std::vector<double> weights, std::vector<Point> points, Pair<int> poly);
    double laplacianIntegral(Pair<int> poly, Polygon p);
    int globalIndex();
    int pointIndex();
};

#endif
