#include <fracture/crack/CrackTip.h>
#include <fracture/geometry/mesh/RemeshAdapter.h>
#include <fracture/config/FractureConfig.h>


CrackTip::CrackTip(PointSegment crack) {
    FractureConfig* config = FractureConfig::instance();

    this->StandardRadius = config->getRatio()*crack.length();
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
    this->StandardRadius = t.StandardRadius;
    this->container_polygon = t.container_polygon;
    this->crackAngle = t.crackAngle;
    this->crackPath = t.crackPath;
}

double CrackTip::calculateAngle(Problem problem, Eigen::VectorXd u) {
    Pair<int> dofB = problem.veamer->pointToDOFS(this->points.b);
    Pair<int> dofC = problem.veamer->pointToDOFS(this->points.c);
    Pair<int> dofD = problem.veamer->pointToDOFS(this->points.d);
    Pair<int> dofE = problem.veamer->pointToDOFS(this->points.e);

    double factor = problem.veamer->getMaterial().stressIntensityFactor()*std::sqrt(2*M_PI/this->usedRadius)*
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

    PolygonChangeData changeData = problem.mesh->breakMesh(this->container_polygon, direction);
    assignLocation(changeData.lastPolygon);

    checkIfFinished(problem, direction);

    return changeData;
}

PolygonChangeData CrackTip::prepareTip(BreakableMesh& mesh) {
    std::vector<int> indexes;
    std::vector<Polygon> newPolygons;
    std::vector<int> affected;

    Point last = this->getPoint();
    Polygon poly = mesh.getPolygon(this->container_polygon);
    BoundingBox box(Point(last.getX()-StandardRadius, last.getY()-StandardRadius),
                    Point(last.getX()+StandardRadius, last.getY()+StandardRadius));

    FractureConfig* config = FractureConfig::instance();

    this->crackAngle = PointSegment(crackPath[crackPath.size() - 2],crackPath.back()).cartesianAngle();

    if(box.fitsInsidePolygon(poly, mesh)){
        affected.push_back(this->container_polygon);
        remeshAndAdapt(StandardRadius, newPolygons, poly, affected, mesh);
    }else{
        UniqueList<int> ringPolygons;
        getDirectNeighbours(this->container_polygon, mesh, ringPolygons);
        RemeshAdapter remesher(ringPolygons.getList(), mesh.getPoints().getList(), mesh);

        Region ringRegion = remesher.getRegion();
        affected.assign(ringPolygons.getList().begin(), ringPolygons.getList().end());
        if (box.fitsInsidePolygon(ringRegion, mesh)) {
            remeshAndAdapt(StandardRadius, newPolygons, ringRegion, ringPolygons.getList(), mesh);
        } else {
            double radius = StandardRadius;
            while(!box.fitsInsidePolygon(ringRegion, mesh)) {
                radius = config->getRatio()*radius;
                box = BoundingBox(Point(last.getX()-radius, last.getY()-radius),
                                  Point(last.getX()+radius, last.getY()+radius));
            }

            remeshAndAdapt(radius, newPolygons, ringRegion, ringPolygons.getList(), mesh);
        }
    }

    std::vector<Polygon> polys;
    for(int i: affected){
        polys.push_back(mesh.getPolygon(i));
    }

    return PolygonChangeData(polys, newPolygons);
}

void CrackTip::remeshAndAdapt(double radius, std::vector<Polygon> &newPolygons, Polygon region,
                              std::vector<int> affectedPolygons, BreakableMesh &mesh) {
    FractureConfig* config = FractureConfig::instance();

    this->usedRadius = radius;
    RosetteGroupGenerator generator(this->getPoint(), config->getRosetteAngle(),radius);
    std::vector<Point> points = generator.getPoints(this->crackAngle);
    RemeshAdapter remesher(region, mesh);

    Triangulation t = remesher.triangulate(points);
    std::unordered_map<int,int> pointMap = remesher.includeNewPoints(mesh.getPoints(), t);

    this->points = CrackTipPoints(pointMap[1], pointMap[2], pointMap[3], pointMap[4]);

    newPolygons = remesher.adaptToMesh(t, affectedPolygons, mesh, pointMap);
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

void CrackTip::checkIfFinished(Problem problem, PointSegment direction) {
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
}

void CrackTip::getDirectNeighbours(int poly, BreakableMesh mesh, UniqueList<int> &neighbours) {
    mesh.getAllNeighbours(poly, neighbours);
    UniqueList<int> neighbours_neighbours;

    for (int i = 0; i < neighbours.size(); ++i) {
        mesh.getAllNeighbours(neighbours.get(i), neighbours_neighbours);
    }

    for (int j = 0; j < neighbours_neighbours.size(); ++j) {
        int candidate = neighbours_neighbours.get(j);
        if(!neighbours.contains(candidate) && mesh.polygonsTouch(poly, candidate)){
            neighbours.push_back(neighbours_neighbours.get(j));
        }
    }
}
