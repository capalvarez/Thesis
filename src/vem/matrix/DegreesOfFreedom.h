#ifndef THESIS_DEGREESOFFREEDOM_H
#define THESIS_DEGREESOFFREEDOM_H

#include <vector>
#include <models/basic/Point.h>
#include <models/polygon/Polygon.h>


class DegreesOfFreedom {
private:
    int order;

    std::vector<int> vertex;
    std::vector<int> edges;
    std::vector<int> inner;
public:
    DegreesOfFreedom(Polygon p, int k, std::vector<Point>& points);
    int numberOfDOF();
    std::pair<double,double> normal(int k, std::vector<Point> points);
};


#endif