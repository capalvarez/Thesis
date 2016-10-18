#ifndef THESIS_CRACK_H
#define THESIS_CRACK_H

#include <x-poly/models/basic/Point.h>
#include <vector>
#include <veamy/models/Element.h>
#include <fracture/models/geometry/BreakableMesh.h>
#include <fracture/models/crack/CrackTip.h>
#include <fracture/models/geometry/structures/BrokenMeshInfo.h>


class Crack {
private:
    CrackTip init;
    CrackTip end;
public:
    Crack();
    Crack(BreakableMesh mesh, Point init, Point end);

    PolygonChangeData grow(BreakableMesh m, Eigen::VectorXd u);
    PolygonChangeData prepareTip(BreakableMesh m);
    bool isFinished(BreakableMesh mesh);

    void initializeCrack(BreakableMesh mesh);
};


#endif
