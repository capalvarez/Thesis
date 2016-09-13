#ifndef THESIS_INNERDOF_H
#define THESIS_INNERDOF_H

#include <models/integration/IntegrationPolygon.h>
#include <utilities/operations.h>
#include "DOF.h"
#include <veamy/models/integration/functions/MaMbFunction.h>

class InnerDOF : public DOF{
private:
    Pair<int> alpha;
public:
    InnerDOF(Pair<int> a, int index);

    double getValue(std::vector<Point> points, Pair<int> coeffs, Polygon p);
    double lineIntegral(int local_id, std::vector<int> elementDOFS, DOFS globalDOFS, int k, Polygon p, std::vector<double> weights, std::vector<Point> points, Pair<int> poly);
    double laplacianIntegral(Pair<int> poly, Polygon p);
    int globalIndex();
    int pointIndex();
};

#endif
