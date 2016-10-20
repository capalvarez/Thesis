#include <fracture/models/crack/Crack.h>

Crack::Crack() {}

Crack::Crack(Point init, Point end) {
    //TODO: Ask the user for speed!
    this->init = CrackTip(Segment<Point>(init, end), 0.01);
    this->end = CrackTip(Segment<Point>(end, init), 0.01);
}

PolygonChangeData Crack::prepareTip(BreakableMesh m) {
    return PolygonChangeData(std::vector<Polygon>(), std::vector<Polygon>(), Polygon());
}

bool Crack::isFinished(BreakableMesh mesh) {
    return init.isFinished(mesh) && end.isFinished(mesh);
}

PolygonChangeData Crack::initializeCrack(BreakableMesh mesh) {
    int poly1 = mesh.findContainerPolygon(this->init.getPoint());
    init.assignLocation(mesh.getPolygon(poly1));

    PolygonChangeData change = mesh.breakMesh(poly1, Segment<Point>(this->init.getPoint(), this->end.getPoint()));
    end.assignLocation(change.lastPolygon);

    return change;
}

PolygonChangeData Crack::grow(BreakableMesh m, Eigen::VectorXd u) {
    return PolygonChangeData(std::vector<Polygon>(), std::vector<Polygon>(), Polygon());
}








