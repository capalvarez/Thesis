#include <veamy/models/constraints/NaturalConstraints.h>

NaturalConstraints::NaturalConstraints() {

}

double NaturalConstraints::lineIntegral(std::vector<Point> points, Polygon p, int DOF_index, int local_index, int k, Eigen::MatrixXd PiZS) {
    //TODO: Represent constraints in neighbour segments

    if(isConstrained(DOF_index)){
        Constraint c = constraints_map[DOF_index];
        List<Segment> constrained = c.getSegments();

        std::vector<double> quadrature;
        std::vector<double> weights;
        lobatto::lobatto_set(k+1,quadrature,weights);

        BasePolinomials b(k);

        double integral = 0;
        int n = constrained.size();

        for (int j = 0; j < n; ++j){
            Segment s = constrained.get(j);

            if(p.containsEdge(s)){
                Point p1 = points[s.getFirst()];
                Point p2 = points[s.getSecond()];

                for (int i = 0; i < weights.size(); ++i) {
                    double x = p1.getX() + (p2.getX() - p1.getX()) * quadrature[i];
                    double y = p1.getY() + (p2.getY() - p1.getY()) * quadrature[i];

                    double xFactor = ((x - p.getCentroid().getX()) / p.getDiameter());
                    double yFactor = ((y - p.getCentroid().getY()) / p.getDiameter());

                    double PiSPhi = 0;

                    for (int alpha = 0; alpha < b.nOfPolinomials(); ++alpha) {
                        Pair<int> a = b.getPolinomial(alpha);

                        PiSPhi += PiZS(alpha, local_index) * operations::power(xFactor, a.first) * operations::power(yFactor, a.second);
                    }

                    integral+=weights[i]*c.getValue(Point(x,y))*PiSPhi;
                }
            }
        }

        return integral;
    }

    return 0;
}

