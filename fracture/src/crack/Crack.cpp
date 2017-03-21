#include <fracture/crack/Crack.h>
#include <fracture/geometry/mesh/RemeshAdapter.h>
#include <fracture/config/FractureConfig.h>

Crack::Crack() {}

Crack::Crack(Point init, Point end, double speed, double ratio) {
    FractureConfig* config = FractureConfig::instance();
    config->setGrowthSpeed(speed);
    config->setCrackRatio(ratio);

    PointSegment crack (init, end);

    this->init = CrackTip(crack);
    this->end = CrackTip(PointSegment(end, init));
}

Crack::Crack(const Crack& c) {
    this->init = c.init;
    this->end = c.end;
}

Crack::Crack(Point init, Point end) {
    PointSegment crack (init, end);

    this->init = CrackTip(crack);
    this->end = CrackTip(PointSegment(end, init));
}

PolygonChangeData Crack::prepareTip(BreakableMesh &m) {
    UniqueList<Polygon> oldP;
    std::vector<Polygon> newP;

    if(this->init.container_polygon  == this->end.container_polygon ){




    }else{
        /*Si chocan los anillos*/
        if(newP.size()==0){

        }else{
            this->prepareTip(this->init, oldP, newP, m);
            this->prepareTip(this->end, oldP, newP, m);
        }



    }


    return PolygonChangeData(oldP.getList(), newP);
}

bool Crack::isFinished() {
    return init.isFinished() && end.isFinished();
}

PolygonChangeData Crack::initializeCrack(BreakableMesh& mesh) {
    int poly1 = mesh.findContainerPolygon(this->init.getPoint());
    init.assignLocation(poly1);

    PolygonChangeData change = mesh.breakMesh(poly1, PointSegment(this->init.getPoint(), this->end.getPoint()));
    end.assignLocation(change.lastPolygon);

    return change;
}

PolygonChangeData Crack::grow(Problem problem, Eigen::VectorXd u) {
    std::vector<Polygon> oldP;
    std::vector<Polygon> newP;

    problem.mesh->printInFile("changed.txt");

    this->grow(this->init, oldP, newP, problem, u);
    this->grow(this->end, oldP, newP, problem, u);

    return PolygonChangeData(oldP, newP);
}

void Crack::prepareTip(CrackTip tip, UniqueList<Polygon> &oldP, std::vector<Polygon> &newP, BreakableMesh &mesh) {
    if(!tip.isFinished()){
        PolygonChangeData data = tip.prepareTip(mesh);

        oldP.push_list(data.oldPolygons);
        newP.insert(newP.end(), data.newPolygons.begin(), data.newPolygons.end());
    }
}

void Crack::grow(CrackTip &tip, std::vector<Polygon> &oldP, std::vector<Polygon> &newP, Problem problem,
                 Eigen::VectorXd u) {
    if(!tip.isFinished()){
        PolygonChangeData data = tip.grow(u, problem);

        oldP.insert(oldP.end(), data.oldPolygons.begin(), data.oldPolygons.end());
        newP.insert(newP.end(), data.newPolygons.begin(), data.newPolygons.end());
    }
}






