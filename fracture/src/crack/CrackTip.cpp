#include <fracture/crack/CrackTip.h>
#include <fracture/geometry/mesh/RemeshAdapter.h>
#include <fracture/config/FractureConfig.h>

CrackTip::CrackTip() {}

CrackTip::CrackTip(PointSegment crack) {
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

    UniqueList<int> n;
    PolygonChangeData changeData = problem.mesh->breakMesh(this->container_polygon, direction, this->isFinished(), n);
    assignLocation(changeData.lastPolygon);

    checkIfFinished(problem, direction);

    return changeData;
}

PolygonChangeData CrackTip::prepareTip(BreakableMesh &mesh, double StandardRadius) {
    std::vector<int> indexes;
    std::vector<Polygon> newPolygons;
    std::vector<int> affected;

    Polygon poly = mesh.getPolygon(this->container_polygon);

    FractureConfig* config = FractureConfig::instance();

    this->crackAngle = PointSegment(crackPath[crackPath.size() - 2],crackPath.back()).cartesianAngle();

    if(fitsBox(StandardRadius, poly, mesh.getPoints().getList())){
        affected.push_back(this->container_polygon);
        remeshAndAdapt(StandardRadius, newPolygons, this->container_polygon, mesh, std::vector<int>());
    } else{
        double candidateRadius = poly.getDiameter()*config->getRatio();

        if(fitsBox(candidateRadius, poly, mesh.getPoints().getList())){
            affected.push_back(this->container_polygon);
            remeshAndAdapt(candidateRadius, newPolygons, this->container_polygon, mesh, std::vector<int>());
        } else{
            std::vector<int> unusedPoints;
            int ringIndex = this->getRingPolygon(mesh, unusedPoints, affected);
            Polygon ringRegion = mesh.getPolygon(ringIndex);
            
            Point last = getPoint();
            BoundingBox box(Point(last.getX()-candidateRadius, last.getY()-candidateRadius),
                            Point(last.getX()+candidateRadius, last.getY()+candidateRadius));

            if (box.fitsInsidePolygon(ringRegion, mesh.getPoints().getList())) {
                remeshAndAdapt(candidateRadius, newPolygons, ringIndex, mesh, unusedPoints);
            } else {
                double radius = candidateRadius;
                while(!box.fitsInsidePolygon(ringRegion, mesh.getPoints().getList())) {
                    radius = config->getRatio()*radius;
                    box = BoundingBox(Point(last.getX()-radius, last.getY()-radius),
                                      Point(last.getX()+radius, last.getY()+radius));
                }

                remeshAndAdapt(radius, newPolygons, ringIndex, mesh, unusedPoints);
            }
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

        if(mesh.isInBorder(this->getPoint())){
            this->hasFinished = true;
            this->container_polygon = container;

            return;
        }

        if(vertexIndex!=-1){
            UniqueList<int> neighbours;
            mesh.getDirectNeighbours(container, neighbours);

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
            if(!this->isFinished()){
                SegmentMap edges = mesh.getSegments();
                Neighbours n = edges.get(container_edge);

                int other = n.getFirst()==container? n.getSecond() : n.getFirst();

                mesh.mergePolygons(container, other);
            }
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

bool CrackTip::fitsBox(double radius, Polygon poly, std::vector<Point> points) {
    Point p = getPoint();
    BoundingBox box(Point(p.getX()-radius, p.getY()-radius),
                    Point(p.getX()+radius, p.getY()+radius));

    return box.fitsInsidePolygon(poly, points);
}

int CrackTip::getRingPolygon(BreakableMesh &mesh, std::vector<int> &unusedPoints, std::vector<int> &affectedPolygons) {
    UniqueList<int> neighbours;
    mesh.getDirectNeighbours(this->container_polygon, neighbours);

    return this->getRingPolygon(mesh, unusedPoints, affectedPolygons, neighbours);
}

int CrackTip::getRingPolygon(BreakableMesh &mesh, std::vector<int> &unusedPoints, std::vector<int> &affectedPolygons,
                             UniqueList<int> neighbours) {
    std::vector<int> mergedPoints;
    std::vector<int> ringPolygonPoints = mesh.getAllPoints(neighbours.getList());
    RemeshAdapter remesher(neighbours.getList(), mesh.getPoints().getList(), mesh, mergedPoints);

    Polygon ringRegion = remesher.getRegion();
    affectedPolygons.assign(neighbours.getList().begin(), neighbours.getList().end());

    unusedPoints = mesh.getUnusedPoints(ringPolygonPoints, mergedPoints);

    mesh.printInFile("afterFirst.txt");
    return remesher.getRegionIndex();
}
