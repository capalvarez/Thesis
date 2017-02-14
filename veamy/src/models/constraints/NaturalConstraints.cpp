#include <veamy/models/constraints/NaturalConstraints.h>

NaturalConstraints::NaturalConstraints() {

}

double NaturalConstraints::lineIntegral(std::vector<Point> points, Polygon p, int point, int DOF_index) {
    if(isConstrained(DOF_index)){
        double integral = 0;

        std::vector<int> polygonPoints = p.getPoints();
        int n = (int) polygonPoints.size();

        IndexSegment prev (polygonPoints[(n + point -1)%n], polygonPoints[point]);
        IndexSegment next (polygonPoints[point], polygonPoints[(n + point + 1)%n]);

        if(segment_map.find(prev)!=segment_map.end()){
            Constraint c = segment_map[prev];

            //TODO: Check convergence with first order aproximation
            integral += 0.5*c.getValue(points[prev.getFirst()]) + 0.5*c.getValue(points[prev.getSecond()]);
        }

        if(segment_map.find(next)!=segment_map.end()){
            Constraint c = segment_map[next];

            //TODO: Check convergence with first order aproximation
            integral += 0.5*c.getValue(points[next.getFirst()]) + 0.5*c.getValue(points[next.getSecond()]);
        }

        return integral;
    }

    return 0;
}

