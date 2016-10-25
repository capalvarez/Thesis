#ifndef THESIS_CRACKTIP_H
#define THESIS_CRACKTIP_H

#include <x-poly/models/basic/Point.h>
#include <x-poly/models/polygon/Polygon.h>
#include <veamy/lib/Eigen/Dense>
#include <fracture/models/geometry/BreakableMesh.h>

class CrackTip {
private:
    double length;
    std::vector<Point> crackPath;
    Polygon container;

    void addPointToPath(double angle);
    double calculateAngle();
public:
    CrackTip();
    CrackTip(Segment<Point> crack, double length);
    Segment<Point> grow(BreakableMesh mesh, Eigen::VectorXd u);
    PolygonChangeData prepareTip(BreakableMesh mesh);
    bool isFinished(BreakableMesh mesh);
    void assignLocation(Polygon& polygon);
    Point getPoint();

};

#endif
