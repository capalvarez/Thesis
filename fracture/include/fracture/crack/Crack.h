#ifndef THESIS_CRACK_H
#define THESIS_CRACK_H

#include <x-poly/models/basic/Point.h>
#include <vector>
#include <veamy/models/Element.h>
#include <fracture/geometry/BreakableMesh.h>
#include <fracture/crack/CrackTip.h>

class Crack {
private:
    CrackTip init;
    CrackTip end;

    void prepareTip(CrackTip tip, UniqueList<Polygon> &oldP, std::vector<Polygon> &newP, BreakableMesh &mesh);
    void grow(CrackTip &tip, std::vector<Polygon> &oldP, std::vector<Polygon> &newP, Problem problem, Eigen::VectorXd u);
public:
    Crack();
    Crack(Point init, Point end);
    Crack(Point init, Point end, double speed, double ratio);
    Crack(const Crack& c);

    PolygonChangeData grow(Problem problem, Eigen::VectorXd u);
    PolygonChangeData prepareTip(BreakableMesh &m);
    bool isFinished(BreakableMesh mesh);

    PolygonChangeData initializeCrack(BreakableMesh &mesh);
};


#endif
