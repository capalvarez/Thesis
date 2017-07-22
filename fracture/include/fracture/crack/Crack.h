#ifndef THESIS_CRACK_H
#define THESIS_CRACK_H

#include <x-poly/models/basic/Point.h>
#include <vector>
#include <veamy/models/Element.h>
#include <fracture/geometry/BreakableMesh.h>
#include <fracture/crack/CrackTip.h>
#include <utilities/Deque.h>

class Crack {
private:
    CrackTip init;
    CrackTip end;
    Deque<Pair<int>> crackPath;
    double StandardRadius;

    std::vector<Pair<int>> prepareTip(CrackTip &tip, UniqueList<Polygon> &oldP, std::vector<Polygon> &newP,
                                      BreakableMesh &mesh,
                                      std::vector<Pair<int>> previousCrackPoints);
    void grow(CrackTip &tip, std::vector<Polygon> &oldP, std::vector<Polygon> &newP, Problem problem, Eigen::VectorXd u,
                  UniqueList<Pair<int>> &crackPoints, PointSegment previousCrackSegment);
    std::vector<Pair<int>> adjustBoxes(CrackTip &tip, BreakableMesh &mesh, std::vector<Pair<int>> previousCrackPoints,
                                              UniqueList<Polygon> &oldPolygons, std::vector<int> &unusedPoints, IndexSegment& crackEntry);
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

    friend class CrackTip;
};


#endif
