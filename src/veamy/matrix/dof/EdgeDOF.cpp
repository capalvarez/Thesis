#include <models/Edge.h>
#include <utilities/operations.h>
#include "EdgeDOF.h"


EdgeDOF::EdgeDOF(int i) : OuterDOF(i){}


double EdgeDOF::lineIntegral(int local_id, int k, Polygon p, std::vector<double> weights, std::vector<Point> points, Pair<int> poly) {
    double integral = 0;
    int n = p.numberOfSides();
    int e = (index-n)/(k-1);

    Edge edge (e, (n+e+1)%n);
    Pair<double> normal = edge.getNormal(points);
    std::vector<int> neighbours = edge.getDOFsInside(k,n);

    for(int i=0;i<neighbours.size();i++){
        integral += weights[i]*normal.dot(operations::gradient(poly, p, points[neighbours[i]]))*
                operations::kronecker(neighbours[i], index);
    }

    return integral;
}


