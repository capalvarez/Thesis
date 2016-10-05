#ifndef THESIS_CRACK_H
#define THESIS_CRACK_H

#include <x-poly/models/basic/Point.h>
#include <vector>
#include <veamy/models/Element.h>
#include "CrackTip.h"
#include "geometry/BreakableMesh.h"

class Crack {
private:
    std::vector<CrackTip> crackTip;
public:
    Crack();
    Crack(BreakableMesh mesh, Point init, Point end);
    Crack(BreakableMesh mesh, Point init, double angle, double length);

    std::vector<Polygon> grow(BreakableMesh m, Eigen::VectorXd u);
    std::vector<Polygon> prepareTip(BreakableMesh m);
    bool isFinished(BreakableMesh mesh);
};


#endif
