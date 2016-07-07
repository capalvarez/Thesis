#include "operations.h"

namespace operations{
    std::pair<double, double> gradient(std::pair<int, int> polinomial, Polygon p, Point point) {
        double xFactor = (point.getX()-p.getCentroid().getX())/p.getDiameter();
        double yFactor = (point.getY()-p.getCentroid().getY())/p.getDiameter();

        return std::pair<double, double>(
                std::make_pair((polinomial.first)*1/p.getDiameter()*pow(xFactor, polinomial.first-1)*pow(yFactor,polinomial.second) ,
                               (polinomial.second)*1/p.getDiameter()*pow(xFactor,polinomial.first) *pow(yFactor, polinomial.second-1)));
    }

    double laplacian(std::pair<int, int> polinomial, Polygon p, Point point) {
        double xFactor = (point.getX()-p.getCentroid().getX())/p.getDiameter();
        double yFactor = (point.getY()-p.getCentroid().getY())/p.getDiameter();

        return ((polinomial.first)*(polinomial.first-1)*pow(xFactor, polinomial.first-2)*pow(yFactor,polinomial.second) +
               (polinomial.second)*(polinomial.second-1)*pow(xFactor,polinomial.first) *pow(yFactor, polinomial.second-2))*1/p.getDiameter();
    }


    double dot(std::pair<double, double> v1, std::pair<double, double> v2) {
        return v1.first*v2.first + v1.second*v2.second;
    }

    std::pair<double,double> normal(Point p1, Point p2){
        return std::make_pair(-(p2.getY()-p1.getY()), p2.getX()-p1.getX());
    };
}

