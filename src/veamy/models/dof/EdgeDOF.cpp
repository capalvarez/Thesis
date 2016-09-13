#include <models/Edge.h>
#include <utilities/operations.h>
#include "EdgeDOF.h"


EdgeDOF::EdgeDOF(int i, int p, Axis a) : OuterDOF(i, p, a){}


double EdgeDOF::lineIntegral(int local_id, std::vector<int> elementDOFS, DOFS globalDOFS, int k, Polygon p, std::vector<double> weights, std::vector<Point> points, Pair<int> poly) {
    double integral = 0;
    int n = p.numberOfSides();
    int e = (local_id-n)/(k-1);

    Edge edge (e, (n+e+1)%n);
    Pair<double> normal = edge.getNormal(globalDOFS, points);
    std::vector<int> local_neighbours = edge.getDOFsInside(k,n);

    for(int i=0;i<local_neighbours.size();i++){
        integral += weights[i]*normal.dot(operations::gradient(poly, p, points[globalDOFS.get(elementDOFS[local_neighbours[i]])->pointIndex()]))*
                operations::kronecker(local_neighbours[i], local_id);
    }

    return integral;
}


