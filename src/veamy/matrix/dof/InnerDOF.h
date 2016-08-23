#ifndef THESIS_INNERDOF_H
#define THESIS_INNERDOF_H


#include "DOF.h"

class InnerDOF : public DOF{
private:
    Pair<int> alpha;
public:
    InnerDOF(Pair<int> a);

    double getValue(std::vector<Point> points, Pair<int> coeffs, Polygon p);
    double lineIntegral(int local_id, int k, Polygon p, std::vector<double> weights, std::vector<Point> points, Pair<int> poly);
    double laplacianIntegral(Pair<int> poly, Polygon p);
};

#endif
