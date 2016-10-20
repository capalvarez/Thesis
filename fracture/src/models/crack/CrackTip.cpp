#include <fracture/models/crack/CrackTip.h>

CrackTip::CrackTip(Segment<Point> crack, double length) {
    this->length = length;
    crackPath.push_back(crack.getSecond());
    crackPath.push_back(crack.getFirst());
}

void CrackTip::addPointToPath(double angle) {

}

double CrackTip::calculateAngle() {

    return 0;
}

Segment<Point> CrackTip::grow(BreakableMesh mesh, Eigen::VectorXd u) {




}

PolygonChangeData CrackTip::prepareTip(BreakableMesh mesh) {




}

bool CrackTip::isFinished(BreakableMesh mesh) {
    return mesh.isInBoundary(crackPath.back());
}

void CrackTip::assignLocation(Polygon polygon) {
    this->container = polygon;
}

CrackTip::CrackTip() {}

Point CrackTip::getPoint() {
    return this->crackPath.back();
}




