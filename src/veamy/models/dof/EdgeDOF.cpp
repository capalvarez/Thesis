#include "EdgeDOF.h"

EdgeDOF::EdgeDOF(int i, int p, Axis a) : OuterDOF(i, p, a){}


double EdgeDOF::lineIntegral(int local_id, std::vector<int> elementDOFS, std::vector<DOF*> globalDOFS, int k, Polygon p, std::vector<double> weights, std::vector<Point> points, Pair<int> poly) {
    double integral = 0;
    int n = p.numberOfSides();
    int point = local_id/2;
    int e = (point-n)/(k-1);

    Edge edge (e, (n+e+1)%n);
    Pair<double> normal = edge.getNormal(p.getPoints(), points);
    std::vector<int> local_neighbours = edge.getDOFsInside(k,n);

    for(int i=0;i<local_neighbours.size();i++){
        integral += weights[i/2]*normal.dot(operations::gradient(poly, p, points[globalDOFS[elementDOFS[local_neighbours[i]]]->pointIndex()]))*
                operations::kronecker(local_neighbours[i], local_id);
    }

    return integral;
}


