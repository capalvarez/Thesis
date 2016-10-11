#include <veamy/models/constraints/NaturalConstraints.h>

NaturalConstraints::NaturalConstraints() {

}

double NaturalConstraints::lineIntegral(std::vector<Point> points, Polygon p, int point, int DOF_index) {
    if(isConstrained(DOF_index)){
        double integral = 0;

        std::vector<int> polygonPoints = p.getPoints();
        int n = (int) polygonPoints.size();

        Segment prev (polygonPoints[(n + point -1)%n], polygonPoints[point]);
        Segment next (polygonPoints[point], polygonPoints[(n + point + 1)%n]);

        if(constrained_segments.find(prev)!=constrained_segments.end()){
            Constraint c = constrained_segments[prev];

            //TODO: Check convergence with first order aproximation
            integral += 0.5*c.getValue(points[prev.getFirst()]) + 0.5*c.getValue(points[prev.getSecond()]);
        }

        if(constrained_segments.find(next)!=constrained_segments.end()){
            Constraint c = constrained_segments[next];

            //TODO: Check convergence with first order aproximation
            integral += 0.5*c.getValue(points[next.getFirst()]) + 0.5*c.getValue(points[next.getSecond()]);
        }

        return integral;
    }

    return 0;
}

