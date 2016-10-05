#include <x-poly/models/Mesh.h>
#include "Crack.h"


Crack::Crack() {

}

Crack::Crack(Point init, Point end) {

}

Crack::Crack(Point init, double angle, double length) {

}


std::vector<Polygon> Crack::grow(Mesh m, Eigen::VectorXd u) {
    for(int i=0;i<crackTip.size();i++){
        Point tip = crackTip[i].grow(m,u);
        std::vector<Polygon> newPolygons = m.breakMesh();
    }




    return std::vector<Polygon>();
}

std::vector<Polygon> Crack::prepareTip(Mesh m) {
    return std::vector<Polygon>();
}




