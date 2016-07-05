#include "BasePolinomials.h"


BasePolinomials::BasePolinomials(int k) {
    this->polinomials.push_back(std::make_pair(0,0));

    for(int i=1;i<=k; i++){
        for(int j=0; j<=i; j++){
            this->polinomials.push_back(std::make_pair(i-j, j));
        }
    }
}

std::vector<std::pair<int, int> > BasePolinomials::getPolinomials() {
    return this->polinomials;
}


std::pair<int, int> BasePolinomials::getPolinomial(int i) {
    return this->polinomials[i];
}


int BasePolinomials::nOfPolinomials() {
    return (int) this->polinomials.size();
}






