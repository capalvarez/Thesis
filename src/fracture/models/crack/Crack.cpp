#include <x-poly/models/Mesh.h>
#include <geometry/structures/BrokenMeshInfo.h>
#include "Crack.h"
#include "DeadCrackTip.h"

Crack::Crack() {}

Crack::Crack(BreakableMesh mesh, Point init, Point end) {
    bool tip1 = mesh.isInBoundary(init);
    bool tip2 = mesh.isInBoundary(end);

    //TODO: Ask the user for speed!
    if(tip1 && tip2){
        crackTip.push_back(DeadCrackTip());
        return;
    }

    if(tip1){
        crackTip.push_back(CrackTip(Segment<Point>(init, end), 0.01));
        return;
    }

    if(tip2){
        crackTip.push_back(CrackTip(Segment<Point>(end, init), 0.01));
        return;
    }

    crackTip.push_back(CrackTip(Segment<Point>(init, end), 0.01));
    crackTip.push_back(CrackTip(Segment<Point>(end, init), 0.01));
}

Crack::Crack(BreakableMesh mesh, Point init, double angle, double length) {

}

std::vector<Polygon> Crack::grow(BreakableMesh m, Eigen::VectorXd u) {
    std::vector<Polygon> changedPolygons;

    for(int i=0;i<crackTip.size();i++){
        Point tip = crackTip[i].grow(m,u);
        BrokenMeshInfo polygons = m.breakMesh();
        tip.assignLocation();

        changedPolygons.assign();
    }

    return changedPolygons;
}

std::vector<Polygon> Crack::prepareTip(BreakableMesh m) {
    return std::vector<Polygon>();
}

bool Crack::isFinished(BreakableMesh mesh) {
    bool finished = true;

    for (int i = 0; i < crackTip.size(); ++i) {
        finished = finished && crackTip[i].isFinished(mesh);
    }

    return finished;
}






