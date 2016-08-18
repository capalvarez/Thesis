#ifndef THESIS_INNERDOF_H
#define THESIS_INNERDOF_H


#include "DOF.h"

class InnerDOF : public DOF{
private:
    Pair<int> alpha;
public:
    double getValue(std::vector<Point> points, Pair<int> coeffs, Polygon p);
};

#endif
