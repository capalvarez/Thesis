#ifndef THESIS_BASEPOLINOMIALS_H
#define THESIS_BASEPOLINOMIALS_H
#include <utility>
#include <vector>

class BasePolinomials {
private:
    std::vector<std::pair<int,int> > polinomials;
public:
    BasePolinomials(int k);
    std::vector<std::pair<int,int> > getPolinomials();
    std::pair<int,int> getPolinomial(int i);
    int nOfPolinomials();
};


#endif
