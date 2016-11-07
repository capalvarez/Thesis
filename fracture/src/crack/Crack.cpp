#include <fracture/crack/Crack.h>
#include <fracture/geometry/mesh/RemeshAdapter.h>

Crack::Crack() {}

Crack::Crack(Point init, Point end, double speed, double ratio) {
    Segment<Point> crack (init, end);

    this->init = CrackTip(crack, speed, crack.length()*ratio);
    this->end = CrackTip(Segment<Point>(end, init), speed, crack.length()*ratio);
}

Crack::Crack(const Crack& c) {
    this->init = c.init;
    this->end = c.end;
}

PolygonChangeData Crack::prepareTip(BreakableMesh &m) {
    std::vector<Polygon> oldP;
    std::vector<Polygon> newP;

    std::set<int> tip1 = this->init.generateTipPoints(m);
    std::set<int> tip2 = this->end.generateTipPoints(m);

    const bool is_affected = tip1.find(this->end.getPolygon()) != tip1.end();

    if(this->init.getPolygon() == this->end.getPolygon() || is_affected){
        std::vector<Point> tip_points1 = this->init.getTipPoints();
        std::vector<Point> tip_points2 = this->end.getTipPoints();
        tip_points1.insert(tip_points1.end(), tip_points2.begin(), tip_points2.end());

        std::vector<Polygon> changed1 = this->init.getChangedPolygons();
        std::vector<Polygon> changed2 = this->end.getChangedPolygons();
        changed1.insert(changed1.end(), changed2.begin(), changed2.end());

        RemeshAdapter remesher (changed1, m.getPoints().getList());

        std::vector<int> changedPolygons;
        std::set_union(tip1.begin(), tip1.end(), tip2.begin(), tip2.end(), std::back_inserter(changedPolygons));

        std::vector<Polygon> newPolygons = remesher.remesh(tip_points1, changedPolygons, m);
        newP.insert(newP.end(), newPolygons.begin(), newPolygons.end());
        oldP.insert(oldP.end(), changed1.begin(), changed1.end());

    }else{
        this->prepareTip(this->init, oldP, newP, m);
        this->prepareTip(this->end, oldP, newP, m);
    }

    m.printInFile("test.txt");
    return PolygonChangeData(oldP, newP);
}

bool Crack::isFinished(BreakableMesh mesh) {
    return init.isFinished(mesh) && end.isFinished(mesh);
}

PolygonChangeData Crack::initializeCrack(BreakableMesh& mesh) {
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

void Crack::prepareTip(CrackTip tip, std::vector<Polygon> &oldP, std::vector<Polygon> &newP, BreakableMesh &mesh) {
    if(!tip.isFinished(mesh)){
        PolygonChangeData data = tip.prepareTip(mesh);

        oldP.insert(oldP.end(), data.oldPolygons.begin(), data.oldPolygons.end());
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






