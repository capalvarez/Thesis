#include <models/Edge.h>
#include <utilities/operations.h>
#include "VertexDOF.h"


VertexDOF::VertexDOF(int i, int p, Axis a) : OuterDOF(i, p, a){}


double VertexDOF::lineIntegral(int local_id, std::vector<int> elementDOFS, DOFS globalDOFS, int k, Polygon p, std::vector<double> weights, std::vector<Point> points, Pair<int> poly) {
    double integral = 0;
    int n = p.numberOfSides();

    Edge prev ((n+local_id-1)%n, local_id);
    Edge next (local_id, (n+local_id+1)%n);

    Pair<double> prevNormal = prev.getNormal(globalDOFS,points);
    Pair<double> nextNormal = next.getNormal(globalDOFS,points);

    std::vector<int> prev_points = prev.getDOFsInside(k, n);
    std::vector<int> next_points = next.getDOFsInside(k, n);

    for(int i=0;i<prev_points.size();i++){
        integral += weights[i]*prevNormal.dot(operations::gradient(poly,p,points[globalDOFS.get(elementDOFS[prev_points[i]])->pointIndex()]))*
                operations::kronecker(local_id, prev_points[i]);
    }

    for(int i=0;i<next_points.size();i++){
        Pair<double> val1 = operations::gradient(poly,p,points[globalDOFS.get(elementDOFS[next_points[i]])->pointIndex()]);
        double val2 = nextNormal.dot(val1);
        double val3 = operations::kronecker(local_id, next_points[i]);

        integral += weights[i]*val2*val3;
    }

    return integral;
}




