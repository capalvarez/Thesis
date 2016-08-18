#ifndef THESIS_OUTERDOF_H
#define THESIS_OUTERDOF_H


#include <x-poly/models/polygon/Polygon.h>
#include <utilities/Pair.h>

class OuterDOF {
private:
    int index;
public:
    OuterDOF(int i);

    double getValue(std::vector<Point> points, Pair<int> coeffs, Polygon p);
};


#endif //THESIS_OUTERDOF_H
