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
    this->hasFinished = t.hasFinished;
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

    reassignContainer(*problem.mesh);
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

    if(box.fitsInsidePolygon(poly, mesh.getPoints().getList())){
        affected.push_back(this->container_polygon);
        remeshAndAdapt(StandardRadius, newPolygons, this->container_polygon, mesh, std::vector<int>());
    }else{
        UniqueList<int> ringPolygons;
        getDirectNeighbours(this->container_polygon, mesh, ringPolygons);

        std::vector<int> mergedPoints;
        std::vector<int> ringPolygonPoints = mesh.getAllPoints(ringPolygons.getList());
        RemeshAdapter remesher(ringPolygons.getList(), mesh.getPoints().getList(), mesh, mergedPoints);

        Polygon ringRegion = remesher.getRegion();
        affected.assign(ringPolygons.getList().begin(), ringPolygons.getList().end());
        if (box.fitsInsidePolygon(ringRegion, mesh.getPoints().getList())) {
            remeshAndAdapt(StandardRadius, newPolygons, remesher.getRegionIndex(), mesh,
                           mesh.getUnusedPoints(ringPolygonPoints, mergedPoints));
        } else {
            double radius = StandardRadius;
            while(!box.fitsInsidePolygon(ringRegion, mesh.getPoints().getList())) {
                radius = config->getRatio()*radius;
                box = BoundingBox(Point(last.getX()-radius, last.getY()-radius),
                                  Point(last.getX()+radius, last.getY()+radius));
            }

            remeshAndAdapt(radius, newPolygons, remesher.getRegionIndex(), mesh,
                           mesh.getUnusedPoints(ringPolygonPoints, mergedPoints));
        }
    }

    std::vector<Polygon> polys;
    for(int i: affected){
        polys.push_back(mesh.getPolygon(i));
    }

    return PolygonChangeData(polys, newPolygons);
}

void CrackTip::remeshAndAdapt(double radius, std::vector<Polygon> &newPolygons, int region, BreakableMesh &mesh,
                              std::vector<int> oldPoints) {
    FractureConfig* config = FractureConfig::instance();

    this->usedRadius = radius;
    RosetteGroupGenerator generator(this->getPoint(), config->getRosetteAngle(),radius);
    std::vector<Point> points = generator.getPoints(this->crackAngle);

    for (int i : oldPoints) {
        points.push_back(mesh.getPoint(i));
    }

    RemeshAdapter remesher(mesh.getPolygon(region), region);

    Triangulation t = remesher.triangulate(points, mesh.getPoints().getList());
    std::unordered_map<int,int> pointMap = remesher.includeNewPoints(mesh.getPoints(), t);

    mesh.printInFile("beforeAdapt.txt");
    this->points = CrackTipPoints(pointMap[1], pointMap[2], pointMap[3], pointMap[4]);

    newPolygons = remesher.adaptToMesh(t, mesh, pointMap);
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

void CrackTip::reassignContainer(BreakableMesh& mesh) {
    int container = mesh.findContainerPolygon(this->getPoint());
    Polygon poly = mesh.getPolygon(container);

    IndexSegment container_edge = poly.containerEdge(mesh.getPoints().getList(), this->getPoint());

    if(container_edge.getFirst()!=-1){
        int vertexIndex = -1;

        if(mesh.getPoint(container_edge.getFirst())==this->getPoint() ){
            vertexIndex = container_edge.getFirst();
        }else{
             if(mesh.getPoint(container_edge.getSecond())==this->getPoint()){
                 vertexIndex = container_edge.getSecond();
             }
        }

        if(mesh.getPoint(vertexIndex).isInBoundary()){
            this->hasFinished = true;
            return;
        }

        if(vertexIndex!=-1){
            UniqueList<int> neighbours;
            this->getDirectNeighbours(container, mesh, neighbours);

            std::vector<int> vertexContainers;
            for (int i = 0; i < neighbours.size(); ++i) {
                Polygon neighbour = mesh.getPolygon(neighbours[i]);

                if(neighbour.isVertex(vertexIndex)){
                    vertexContainers.push_back(neighbours[i]);
                }
            }

            int index = mesh.mergePolygons(vertexContainers);
            this->container_polygon = index;

            return;
        }else{
            SegmentMap edges = mesh.getSegments();
            Neighbours n = edges.get(container_edge);

            int other = n.getFirst()==container? n.getSecond() : n.getFirst();

            mesh.mergePolygons(container, other);
        }
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
        mesh.getAllNeighbours(neighbours[i], neighbours_neighbours);
    }

    for (int j = 0; j < neighbours_neighbours.size(); ++j) {
        int candidate = neighbours_neighbours[j];
        if(!neighbours.contains(candidate) && mesh.polygonsTouch(poly, candidate)){
            neighbours.push_back(neighbours_neighbours[j]);
        }
    }
}
