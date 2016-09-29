#ifndef THESIS_MAMBFUNCTION_H
#define THESIS_MAMBFUNCTION_H

#include <veamy/matrix/integration/IntegrationFunction.h>

class MaMbFunction : public IntegrationFunction {
private:
    Pair<int> a;
    Pair<int> b;
    Polygon poly;
public:
    MaMbFunction(Pair<int> a, Pair<int> b, Polygon p){
        this->a = a;
        this->b = b;
        this->poly = p;
    }

    double call(double x, double y){
        double xFactor = ((x - poly.getCentroid().getX())/poly.getDiameter());
        double yFactor = ((y - poly.getCentroid().getY())/poly.getDiameter());

        return operations::power(xFactor, a.first + b.first)*
               operations::power(yFactor, a.second + b.second);
    }
};

#endif
