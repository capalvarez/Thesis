#ifndef THESIS_CRACKTIP_H
#define THESIS_CRACKTIP_H

#include <x-poly/models/basic/Point.h>
#include <x-poly/models/polygon/Polygon.h>
#include <veamy/lib/Eigen/Dense>
#include <fracture/models/geometry/BreakableMesh.h>
#include <x-poly/models/polygon/Triangle.h>

class CrackTip {
private:
    double length;
    std::vector<Point> crackPath;
    int container_polygon;

    void addPointToPath(double angle);
    double calculateAngle();

    Polygon getTransformedTriangle(Triangle triangle, BreakableMesh mesh, std::unordered_map<int, int> pointMap);
public:
    CrackTip();
    CrackTip(Segment<Point> crack, double length);
    Segment<Point> grow(BreakableMesh& mesh, Eigen::VectorXd u);
    PolygonChangeData prepareTip(BreakableMesh& mesh);
    bool isFinished(BreakableMesh mesh);
    void assignLocation(int polygon);
    Point getPoint();

};

#endif
