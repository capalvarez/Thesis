#ifndef THESIS_CRACKTIP_H
#define THESIS_CRACKTIP_H

#include <x-poly/models/basic/Point.h>
#include <x-poly/models/polygon/Polygon.h>
#include <veamy/lib/Eigen/Dense>
#include <fracture/geometry/BreakableMesh.h>
#include <x-poly/models/polygon/Triangle.h>
#include <veamy/physics/Material.h>
#include <fracture/problem/Problem.h>
#include <fracture/crack/structures/CrackTipPoints.h>
#include <fracture/geometry/generator/RosetteGroupGenerator.h>
#include <x-poly/models/Region.h>
#include <x-poly/voronoi/TriangleMeshGenerator.h>
#include <fracture/utilities/fractureutilities.h>

class CrackTip {
private:
    double radius;
    std::vector<Point> crackPath;
    int container_polygon;
    CrackTipPoints points;
    double crackAngle;

    std::vector<Point> tipPoints;
    std::vector<int> changedPolygons;
    std::vector<int> changedIndex;
    std::vector<int> container_polygons;

    void reassignContainer(Problem problem);
    void findContainerPolygons(std::vector<Polygon> centerPolygons, std::vector<int> indexes,
                               std::vector<Point> points);
public:
    CrackTip();
    CrackTip(PointSegment crack);
    CrackTip(const CrackTip& t);

    void addPointToPath(double angle);
    double calculateAngle(Problem problem, Eigen::VectorXd u);

    PolygonChangeData grow(Eigen::VectorXd u, Problem problem);
    PolygonChangeData prepareTip(BreakableMesh& mesh);
    bool isFinished(BreakableMesh mesh);
    void assignLocation(int polygon);
    Point getPoint();

    std::set<int> generateTipPoints(BreakableMesh mesh);

    friend class Crack;
};

#endif
