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
    double usedRadius;
    std::vector<Point> crackPath;
    int container_polygon;
    CrackTipPoints points;
    double crackAngle;
    std::vector<int> tipTriangles;
    Region ring;

    bool hasFinished = false;

    void checkIfFinished(Problem problem, PointSegment direction);
    void remeshAndAdapt(double radius, std::vector<Polygon> &newPolygons, int region, BreakableMesh &mesh,
                        std::vector<int> oldPoints, std::vector<PointSegment> restrictedSegments);
    void reassignContainer(BreakableMesh& mesh);
    bool fitsBox(double radius, Polygon poly, std::vector<Point> points);
    int getRingPolygon(BreakableMesh &mesh, std::vector<int> &unusedPoints, std::vector<Polygon> &oldPolygons);
    int getRingPolygon(BreakableMesh &mesh, std::vector<int> &unusedPoints, UniqueList<int> neighbours);
public:
    CrackTip();
    CrackTip(PointSegment crack);
    CrackTip(const CrackTip& t);

    void addPointToPath(double angle, BreakableMesh mesh);
    double calculateAngle(Problem problem, Eigen::VectorXd u);

    PolygonChangeData grow(Eigen::VectorXd u, Problem problem);
    PolygonChangeData prepareTip(BreakableMesh &mesh, double StandardRadius, std::vector<int> entryToContainer);
    bool isFinished();
    void assignLocation(int polygon);
    Point getPoint();

    friend class Crack;
};

#endif
