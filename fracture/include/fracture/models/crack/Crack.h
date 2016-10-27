#ifndef THESIS_CRACK_H
#define THESIS_CRACK_H

#include <x-poly/models/basic/Point.h>
#include <vector>
#include <veamy/models/Element.h>
#include <fracture/models/geometry/BreakableMesh.h>
#include <fracture/models/crack/CrackTip.h>

class Crack {
private:
    CrackTip init;
    CrackTip end;
public:
    Crack();
    Crack(Point init, Point end, double speed, double ratio);

    PolygonChangeData grow(Problem problem, Eigen::VectorXd u);
    PolygonChangeData prepareTip(BreakableMesh m);
    bool isFinished(BreakableMesh mesh);

    PolygonChangeData initializeCrack(BreakableMesh mesh);
};


#endif
