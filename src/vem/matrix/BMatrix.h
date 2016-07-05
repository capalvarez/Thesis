#ifndef THESIS_BMATRIX_H
#define THESIS_BMATRIX_H

#include "lib/Eigen/Dense"
#include <models/polygon/Polygon.h>
#include "DegreesOfFreedom.h"
#include "BasePolinomials.h"

class BMatrix {
private:
    Eigen::MatrixXf B;
    std::pair<double,double> gradient(std::pair<int,int> polinomial, Polygon p, Point point);
    double laplacian(std::pair<int, int> polinomial,Polygon p, Point point);
    double dot(std::pair<double, double> v1, std::pair<double, double> v2);

public:
    BMatrix(Polygon p, int k, std::vector<Point> points);
    Eigen::MatrixXf getBMatrix();
};


#endif