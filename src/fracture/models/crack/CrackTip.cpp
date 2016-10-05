#include "CrackTip.h"

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

Point CrackTip::grow(Eigen::VectorXd u) {




}

bool CrackTip::isFinished(BreakableMesh mesh) {
    return mesh.isInBoundary(crackPath.back());
}





