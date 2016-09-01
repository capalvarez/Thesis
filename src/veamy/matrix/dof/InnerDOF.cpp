#include <models/integration/IntegrationPolygon.h>
#include <utilities/operations.h>
#include "InnerDOF.h"

InnerDOF::InnerDOF(Pair<int> a, int index) {
    this->alpha = a;
    this->index = index;
}

double InnerDOF::getValue(std::vector<Point> points, Pair<int> coeffs, Polygon p) {
    IntegrationPolygon polygon (p.getPoints(), points);

    static Polygon poly = p;

    class Function : public IntegrationFunction {
    private:
        Pair<int> c;
        Pair<int> a;
    public:
        Function(Pair<int> c, Pair<int> a){
            this->c = c;
            this->a = a;
            //this->poly = p;
        }

        double call(double x, double y){
            double xFactor = ((x - poly.getCentroid().getX())/poly.getDiameter());
            double yFactor = ((y - poly.getCentroid().getY())/poly.getDiameter());

            return operations::power(xFactor, c.first + a.first)*
                   operations::power(yFactor, c.second + a.second);
        }
    };

    Function* f = new Function(coeffs, alpha);

    double integral = polygon.integrate(f, points);
    delete(f);

    return integral;
}

double InnerDOF::lineIntegral(int local_id, int k, Polygon p, std::vector<double> weights, std::vector<Point> points, Pair<int> poly) {
    return 0;
}

double InnerDOF::laplacianIntegral(Pair<int> poly, Polygon p) {
    return -p.getArea()*operations::laplacian(poly,p);
}

int InnerDOF::globalIndex() {
    return this->index;
}





