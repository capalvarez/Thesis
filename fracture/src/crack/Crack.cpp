#include <fracture/crack/Crack.h>

Crack::Crack() {}

Crack::Crack(Point init, Point end, double speed, double ratio) {
    Segment<Point> crack (init, end);

    this->init = CrackTip(crack, speed, crack.length()*ratio);
    this->end = CrackTip(Segment<Point>(end, init), speed, crack.length()*ratio);
}

PolygonChangeData Crack::prepareTip(BreakableMesh m) {
    std::vector<Polygon> oldP;
    std::vector<Polygon> newP;

    this->prepareTip(this->init, oldP, newP, m);
    this->prepareTip(this->end, oldP, newP, m);

    return PolygonChangeData(oldP, newP);
}

bool Crack::isFinished(BreakableMesh mesh) {
    return init.isFinished(mesh) && end.isFinished(mesh);
}

PolygonChangeData Crack::initializeCrack(BreakableMesh mesh) {
    int poly1 = mesh.findContainerPolygon(this->init.getPoint());
    init.assignLocation(poly1);

    PolygonChangeData change = mesh.breakMesh(poly1, Segment<Point>(this->init.getPoint(), this->end.getPoint()));
    end.assignLocation(change.lastPolygon);

    return change;
}

PolygonChangeData Crack::grow(Problem problem, Eigen::VectorXd u) {
    std::vector<Polygon> oldP;
    std::vector<Polygon> newP;

    this->grow(this->init, oldP, newP, problem, u);
    this->grow(this->end, oldP, newP, problem, u);

    return PolygonChangeData(oldP, newP);
}

void Crack::prepareTip(CrackTip tip, std::vector<Polygon> &oldP, std::vector<Polygon> &newP, BreakableMesh mesh) {
    if(!tip.isFinished(mesh)){
        PolygonChangeData data = tip.prepareTip(mesh);

        oldP.push_back(data.oldPolygons[0]);
        newP.insert(newP.end(), data.newPolygons.begin(), data.newPolygons.end());
    }
}

void Crack::grow(CrackTip tip, std::vector<Polygon> &oldP, std::vector<Polygon> &newP, Problem problem, Eigen::VectorXd u) {
    if(!tip.isFinished(*problem.mesh)){
        PolygonChangeData data = tip.grow(u, problem);

        oldP.insert(oldP.end(), data.oldPolygons.begin(), data.oldPolygons.end());
        newP.insert(newP.end(), data.newPolygons.begin(), data.newPolygons.end());
    }
}






