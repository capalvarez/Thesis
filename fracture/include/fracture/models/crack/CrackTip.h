#ifndef THESIS_CRACKTIP_H
#define THESIS_CRACKTIP_H

#include <x-poly/models/basic/Point.h>
#include <x-poly/models/polygon/Polygon.h>
#include <veamy/lib/Eigen/Dense>
#include <fracture/models/geometry/BreakableMesh.h>
#include <x-poly/models/polygon/Triangle.h>
#include <veamy/physics/Material.h>
#include <fracture/models/problem/Problem.h>
#include <fracture/models/crack/structures/CrackTipPoints.h>
#include <fracture/models/geometry/generator/RosetteGroupGenerator.h>
#include <x-poly/models/Region.h>
#include <x-poly/voronoi/TriangleMeshGenerator.h>


class CrackTip {
private:
    double speed;
    double radius;
    std::vector<Point> crackPath;
    int container_polygon;
    CrackTipPoints points;
    double crackAngle;

    void addPointToPath(double angle);
    double calculateAngle(Problem problem, Eigen::VectorXd u);
public:
    CrackTip();
    CrackTip(Segment<Point> crack, double length, double radius);
    PolygonChangeData grow(Eigen::VectorXd u, Problem problem);
    PolygonChangeData prepareTip(BreakableMesh& mesh);
    bool isFinished(BreakableMesh mesh);
    void assignLocation(int polygon);
    Point getPoint();

};

#endif
