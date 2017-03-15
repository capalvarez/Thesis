#include <fracture/crack/CrackTip.h>
#include <fracture/geometry/mesh/RemeshAdapter.h>
#include <fracture/config/FractureConfig.h>


CrackTip::CrackTip(PointSegment crack) {
    FractureConfig* config = FractureConfig::instance();

    this->radius = config->getRatio()*crack.length();
    crackPath.push_back(crack.getSecond());
    crackPath.push_back(crack.getFirst());
}

void CrackTip::addPointToPath(double angle) {
    FractureConfig* config = FractureConfig::instance();
    Point last = crackPath.back();

    Point newPoint(last.getX() + config->getSpeed()*std::cos(utilities::radian(angle)),
                   last.getY() + config->getSpeed()*std::sin(utilities::radian(angle)));

    this->crackPath.push_back(newPoint);
}

CrackTip::CrackTip(const CrackTip &t) {
    this->points = t.points;
    this->radius = t.radius;
    this->container_polygon = t.container_polygon;
    this->crackAngle = t.crackAngle;
    this->crackPath = t.crackPath;
    this->changedPolygons = t.changedPolygons;
    this->changedIndex = t.changedIndex;
    this->tipPoints = t.tipPoints;
    this->container_polygons.assign(t.container_polygons.begin(),t.container_polygons.end());
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

    reassignContainer(problem);
    problem.mesh->printInFile("changed.txt");
    PointSegment direction(lastPoint, crackPath.back());
    int n = problem.mesh->getPolygonInDirection(this->container_polygons, direction);

    PolygonChangeData changeData = problem.mesh->breakMesh(n, direction);
    assignLocation(changeData.lastPolygon);


    int last;
    int isOutside = problem.mesh->findContainerPolygon(crackPath.back(), last);
    if(isOutside==-1) {
        Polygon& poly = problem.mesh->getPolygon(last);

        std::vector<IndexSegment> polySeg;
        poly.getSegments(polySeg);

        for (int j = 0; j < polySeg.size() ; ++j) {
            Point p;
            bool intersects = polySeg[j].intersection(problem.mesh->getPoints().getList(), direction, p);

            if(intersects){
                hasFinished = true;
                crackPath.pop_back();
                crackPath.push_back(p);
            }
        }
    }

    return changeData;
}

PolygonChangeData CrackTip::prepareTip(BreakableMesh& mesh) {
    std::vector<int> indexes;
    RemeshAdapter remesher(this->changedPolygons, mesh.getPoints().getList(), mesh);

    Triangulation t = remesher.triangulate(tipPoints);
    std::unordered_map<int,int> pointMap = remesher.includeNewPoints(mesh.getPoints(), t);

    this->points = CrackTipPoints(pointMap[1], pointMap[2], pointMap[3], pointMap[4]);

    std::vector<Polygon> newPolygons = remesher.adaptToMesh(t, this->changedIndex, mesh, pointMap, indexes);
    findContainerPolygons(newPolygons, indexes, mesh.getPoints().getList());

    std::vector<Polygon> polys;
    for(int i: this->changedPolygons){
        polys.push_back(mesh.getPolygon(i));
    }

    return PolygonChangeData(polys, newPolygons);
}

bool CrackTip::isFinished() {
    return this->hasFinished;
}

void CrackTip::assignLocation(int polygon) {
    this->container_polygon = polygon;
}

CrackTip::CrackTip() {}

Point CrackTip::getPoint() {
    return this->crackPath.back();
}

std::set<int> CrackTip::generateTipPoints(BreakableMesh mesh) {
    FractureConfig* config = FractureConfig::instance();

    this->crackAngle = PointSegment(crackPath[crackPath.size() - 2],crackPath.back()).cartesianAngle();
    Polygon container = mesh.getPolygon(this->container_polygon);

    RosetteGroupGenerator rosette = RosetteGroupGenerator(this->getPoint(), this->radius, config->getRosetteAngle(),
                                                          container_polygon, container);
    tipPoints = rosette.getPoints(this->crackAngle, mesh);

    this->changedPolygons = fracture_utilities::setToVector(rosette.getChangedPolygons());
    std::copy(this->changedPolygons.begin(), this->changedPolygons.end(), std::back_inserter(this->changedIndex));

    return rosette.getChangedPolygons();
}

void CrackTip::reassignContainer(Problem problem) {
    int container = problem.mesh->findContainerPolygon(this->getPoint());
    Polygon poly = problem.mesh->getPolygon(container);

    IndexSegment container_edge = poly.containerEdge(problem.mesh->getPoints().getList(), this->getPoint());

    if(container_edge.getFirst()!=-1){
        SegmentMap edges = problem.mesh->getSegments();
        Neighbours n = edges.get(container_edge);

        int other = n.getFirst()==container? n.getSecond() : n.getFirst();

        problem.mesh->mergePolygons(container, other);
    }

    this->container_polygon = container;
}

void CrackTip::findContainerPolygons(std::vector<Polygon> centerPolygons, std::vector<int> indexes,
                                     std::vector<Point> points) {
    //TODO: Check for an optimal way of obtaining this index
    int tip = utilities::indexOf(points,crackPath.back());

    for (int i = 0; i < centerPolygons.size(); ++i) {
        Polygon p = centerPolygons[i];

        if(p.isVertex(tip)){
            container_polygons.push_back(indexes[i]);
        }
    }
}
