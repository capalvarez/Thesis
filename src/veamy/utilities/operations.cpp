#include "operations.h"

namespace operations{
    Pair<double> gradient(Pair<int> polinomial, Polygon p, Point point) {
        double xFactor = (point.getX()-p.getCentroid().getX())/p.getDiameter();
        double yFactor = (point.getY()-p.getCentroid().getY())/p.getDiameter();

        return Pair<double>(polinomial.first*power(xFactor,polinomial.first-1)*power(yFactor,polinomial.second)/p.getDiameter(),
                            polinomial.second*power(yFactor, polinomial.second-1)*power(xFactor, polinomial.first)/p.getDiameter());
    }

    double laplacian(Pair<int> polinomial, Polygon p) {
        return ((polinomial.first)*(polinomial.first-1>=0? polinomial.first-1 : 0) +
               (polinomial.second)*(polinomial.second-1>=0? polinomial.second-1: 0))*pow(1/p.getDiameter(),2);
    }

    double power(double base, double exp){
        return base!=0? pow(base,exp) : (exp!=0? 0 : 1);
    }

    int kronecker(int i, int j){
        return i==j? 1 : 0;
    }

}

