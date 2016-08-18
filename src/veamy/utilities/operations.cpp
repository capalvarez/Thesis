#include "operations.h"

namespace operations{
    double polyDerivative(double base, double exp){
        if(base!=0)
            return exp*pow(base, exp-1);
        return 0;
    }

    Pair<double> gradient(Pair<int> polinomial, Polygon p, Point point) {
        double xFactor = (point.getX()-p.getCentroid().getX())/p.getDiameter();
        double yFactor = (point.getY()-p.getCentroid().getY())/p.getDiameter();

        return Pair<double>(polyDerivative(xFactor,polinomial.first)/p.getDiameter()*pow(yFactor,polinomial.second),
                            polyDerivative(yFactor, polinomial.second)/p.getDiameter()*pow(xFactor, polinomial.first));
    }

    double laplacian(Pair<int> polinomial, Polygon p, Point point) {
        double xFactor = (point.getX()-p.getCentroid().getX())/p.getDiameter();
        double yFactor = (point.getY()-p.getCentroid().getY())/p.getDiameter();

        int xPower = polinomial.first-2>=0? polinomial.first-2 : 0;
        int yPower = polinomial.second-2>=0? polinomial.second-2 : 0;

        return ((polinomial.first)*(polinomial.first-1)*pow(xFactor, xPower)*pow(yFactor,polinomial.second) +
               (polinomial.second)*(polinomial.second-1)*pow(xFactor,polinomial.first) *pow(yFactor, yPower))*(1/p.getDiameter());
    }

    double power(double base, double exp){
        return base!=0? pow(base,exp) : 0;
    }

}

