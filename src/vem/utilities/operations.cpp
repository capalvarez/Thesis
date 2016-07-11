#include "operations.h"

namespace operations{
    Pair<double> gradient(Pair<int> polinomial, Polygon p, Point point) {
        double xFactor = (point.getX()-p.getCentroid().getX())/p.getDiameter();
        double yFactor = (point.getY()-p.getCentroid().getY())/p.getDiameter();

        return Pair<double>((polinomial.first)*1/p.getDiameter()*pow(xFactor, polinomial.first-1)*pow(yFactor,polinomial.second) ,
                            (polinomial.second)*1/p.getDiameter()*pow(xFactor,polinomial.first) *pow(yFactor, polinomial.second-1));
    }

    double laplacian(Pair<int> polinomial, Polygon p, Point point) {
        double xFactor = (point.getX()-p.getCentroid().getX())/p.getDiameter();
        double yFactor = (point.getY()-p.getCentroid().getY())/p.getDiameter();

        int xPower = polinomial.first-2>=0? polinomial.first-2 : 0;
        int yPower = polinomial.second-2>=0? polinomial.second-2 : 0;

        return ((polinomial.first)*(polinomial.first-1)*pow(xFactor, xPower)*pow(yFactor,polinomial.second) +
               (polinomial.second)*(polinomial.second-1)*pow(xFactor,polinomial.first) *pow(yFactor, yPower))*(1/p.getDiameter());
    }

    Pair<double> normal(Point p1, Point p2){
        return Pair<double>(-(p2.getY()-p1.getY()), p2.getX()-p1.getX());
    };
}

