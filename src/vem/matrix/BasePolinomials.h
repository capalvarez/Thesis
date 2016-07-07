#ifndef THESIS_BASEPOLINOMIALS_H
#define THESIS_BASEPOLINOMIALS_H
#include <utility>
#include <vector>
#include "utilities/Pair.h"

class BasePolinomials {
private:
    std::vector<Pair<int>> polinomials;
public:
    BasePolinomials(int k);
    std::vector<Pair<int>> getPolinomials();
    Pair<int> getPolinomial(int i);
    int nOfPolinomials();
};


#endif
