#include <models/Edge.h>
#include <utilities/operations.h>
#include "VertexDOF.h"


VertexDOF::VertexDOF(int i) : OuterDOF(i){}


double VertexDOF::lineIntegral(int local_id, int k, Polygon p, std::vector<double> weights, std::vector<Point> points, Pair<int> poly) {
    double integral = 0;
    int n = p.numberOfSides();
    std::vector<int> polyPoints = p.getPoints();

    Edge prev (polyPoints[(n+local_id-1)%n], polyPoints[local_id]);
    Edge next (polyPoints[local_id],polyPoints[(n+local_id+1)%n]);

    Pair<double> prevNormal = prev.getNormal(points);
    Pair<double> nextNormal = next.getNormal(points);

    std::vector<int> prev_points = prev.getDOFsInside(k, n);
    std::vector<int> next_points = next.getDOFsInside(k, n);

    for(int i=0;i<prev_points.size();i++){
        integral += weights[i]*prevNormal.dot(operations::gradient(poly,p,points[prev_points[i]]))*
                operations::kronecker(index, prev_points[i]);
    }

    for(int i=0;i<next_points.size();i++){
        Pair<double> val1 = operations::gradient(poly,p,points[next_points[i]]);
        double val2 = nextNormal.dot(val1);
        double val3 = operations::kronecker(index, next_points[i]);

        integral += weights[i]*val2*val3;
    }

    return integral;
}




