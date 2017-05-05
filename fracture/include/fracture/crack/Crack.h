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
    UniqueList<int> pointIndexes;
    double StandardRadius;

    void prepareTip(CrackTip tip, UniqueList<Polygon> &oldP, std::vector<Polygon> &newP, BreakableMesh &mesh,
                    std::vector<int> entryToContainer);
    void grow(CrackTip &tip, std::vector<Polygon> &oldP, std::vector<Polygon> &newP, Problem problem, Eigen::VectorXd u);
    double adjustBoxes(Polygon initPoly, Polygon endPoly, std::vector<Point> points);
public:
    Crack();
    Crack(Point init, Point end);
    Crack(Point init, Point end, double speed, double ratio);
    Crack(const Crack& c);

    PolygonChangeData grow(Problem problem, Eigen::VectorXd u);
    PolygonChangeData prepareTip(BreakableMesh &m);
    bool isFinished();

    void initializeCrack(BreakableMesh &mesh);
    void printInStream(std::ofstream& file);
};


#endif
