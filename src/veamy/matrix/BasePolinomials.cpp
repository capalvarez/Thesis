#include "BasePolinomials.h"


BasePolinomials::BasePolinomials(int k) {
    if(k>=0){
        this->polinomials.push_back(Pair<int>(0,0));

        for(int i=1;i<=k; i++){
            for(int j=0; j<=i; j++){
                this->polinomials.push_back(Pair<int>(i-j, j));
            }
        }
    }
}

std::vector<Pair<int>> BasePolinomials::getPolinomials() {
    return this->polinomials;
}


Pair<int> BasePolinomials::getPolinomial(int i) {
    return this->polinomials[i];
}


int BasePolinomials::nOfPolinomials() {
    return (int) this->polinomials.size();
}






