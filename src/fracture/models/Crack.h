#ifndef THESIS_CRACK_H
#define THESIS_CRACK_H

#include <x-poly/models/basic/Point.h>
#include <vector>
#include <veamy/models/Element.h>
#include "CrackTip.h"

class Crack {
private:
    std::vector<CrackTip> crackTip;
public:
    Crack();
    Crack(Point init, Point end);
    Crack(Point init, double angle, double length);

    std::vector<Polygon> grow(Mesh m, Eigen::VectorXd u);
    std::vector<Polygon> prepareTip(Mesh m);
};


#endif
