#include <fracture/models/crack/Crack.h>

Crack::Crack() {}

Crack::Crack(Point init, Point end) {
    //TODO: Ask the user for speed!
    this->init = CrackTip(Segment<Point>(init, end), 0.01);
    this->end = CrackTip(Segment<Point>(end, init), 0.01);
}

PolygonChangeData Crack::prepareTip(BreakableMesh m) {
    std::vector<Polygon> oldP;
    std::vector<Polygon> newP;

    if(!this->init.isFinished(m)){
        PolygonChangeData data = this->init.prepareTip(m);

        oldP.push_back(data.oldPolygons[0]);
        newP.insert(newP.end(), data.newPolygons.begin(), data.newPolygons.end());
    }

    if(!this->end.isFinished(m)){
        PolygonChangeData data = this->end.prepareTip(m);

        oldP.push_back(data.oldPolygons[0]);
        newP.insert(newP.end(), data.newPolygons.begin(), data.newPolygons.end());
    }

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

PolygonChangeData Crack::grow(BreakableMesh m, Eigen::VectorXd u) {
    return PolygonChangeData(std::vector<Polygon>(), std::vector<Polygon>(), 0);
}








