#include <fracture/crack/CrackTip.h>
#include <fracture/geometry/mesh/RemeshAdapter.h>

CrackTip::CrackTip(Segment<Point> crack, double speed, double radius) {
    this->speed = speed;
    this->radius = radius;
    crackPath.push_back(crack.getSecond());
    crackPath.push_back(crack.getFirst());
}

void CrackTip::addPointToPath(double angle) {
    Point last = crackPath.back();

    Point newPoint(last.getX() + this->speed*std::cos(utilities::radian(angle)),
                   last.getY() + this->speed*std::sin(utilities::radian(angle)));

    this->crackPath.push_back(newPoint);
}

CrackTip::CrackTip(const CrackTip &t) {
    this->points = t.points;
    this->container_polygon = t.container_polygon;
    this->crackAngle = t.crackAngle;
    this->crackPath = t.crackPath;
    this->speed = t.speed;
    this->radius = t.radius;
    this->changedPolygons = t.changedPolygons;
    this->changedIndex = t.changedIndex;
    this->tipPoints = t.tipPoints;
}

double CrackTip::calculateAngle(Problem problem, Eigen::VectorXd u) {
    Pair<int> dofB = problem.veamer->pointToDOFS(this->points.b);
    Pair<int> dofC = problem.veamer->pointToDOFS(this->points.c);
    Pair<int> dofD = problem.veamer->pointToDOFS(this->points.d);
    Pair<int> dofE = problem.veamer->pointToDOFS(this->points.e);

    double factor = problem.veamer->getMaterial().stressIntensityFactor()*std::sqrt(2*M_PI/this->radius)*
                    1/std::cos(utilities::radian(this->crackAngle));

    double kI = factor * (4*(u[dofB.second] - u[dofD.second]) - (u[dofC.second] - u[dofE.second])/2);
    double kII = factor * (4*(u[dofB.first] - u[dofD.first]) - (u[dofC.first] - u[dofE.first])/2);


    if(kII!=0){
        double r = kI/kII;

        return 2*std::atan(r/4 - utilities::sign(kII)/4*std::sqrt((std::pow(r,2) + 8)))  + this->crackAngle;
    }else{
        return this->crackAngle;
    }
}

PolygonChangeData CrackTip::grow(Eigen::VectorXd u, Problem problem) {
    double angle = calculateAngle(problem, u);
    Point lastPoint = crackPath.back();
    addPointToPath(angle);

    this->container_polygon = problem.mesh->findContainerPolygon(this->getPoint());

    PolygonChangeData changeData = problem.mesh->breakMesh(this->container_polygon, Segment<Point>(lastPoint, crackPath.back()));
    assignLocation(changeData.lastPolygon);

    return changeData;
}

PolygonChangeData CrackTip::prepareTip(BreakableMesh& mesh) {
    RemeshAdapter remesher(this->changedPolygons, mesh.getPoints().getList());

    Triangulation t = remesher.triangulate(tipPoints);
    std::unordered_map<int,int> pointMap = remesher.includeNewPoints(mesh.getPoints(), t);

    this->points = CrackTipPoints(pointMap[1], pointMap[2], pointMap[3], pointMap[4]);

    std::vector<Polygon> newPolygons = remesher.adaptToMesh(t, this->changedIndex, mesh, pointMap);

    return PolygonChangeData(this->changedPolygons, newPolygons);
}

bool CrackTip::isFinished(BreakableMesh mesh) {
    return mesh.isInBoundary(crackPath.back());
}

void CrackTip::assignLocation(int polygon) {
    this->container_polygon = polygon;
}

CrackTip::CrackTip() {}

Point CrackTip::getPoint() {
    return this->crackPath.back();
}

std::set<int> CrackTip::generateTipPoints(BreakableMesh mesh) {
    this->crackAngle = Segment<Point>(crackPath[crackPath.size() - 2],crackPath.back()).cartesianAngle(crackPath);
    Polygon container = mesh.getPolygon(this->container_polygon);

     // TODO: I know 45 is about right, but don't hardcode it
    RosetteGroupGenerator rosette = RosetteGroupGenerator(this->getPoint(), this->radius, 45, container_polygon, container);
    tipPoints = rosette.getPoints(this->crackAngle, mesh);

    this->changedPolygons = rosette.getChangedPolygons(mesh);
    std::set<int> indexes = rosette.getChangedPolygons();

    std::copy(indexes.begin(), indexes.end(), std::back_inserter(this->changedIndex));

    return indexes;
}
