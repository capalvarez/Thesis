#include <fracture/crack/CrackTip.h>
#include <fracture/geometry/mesh/RemeshAdapter.h>
#include <fracture/config/FractureConfig.h>

CrackTip::CrackTip() {}

CrackTip::CrackTip(Point crack) {
    this->tipPoint = crack;
}

void CrackTip::addPointToPath(double angle, BreakableMesh mesh) {
    FractureConfig* config = FractureConfig::instance();
    Point last = this->getPoint();

    Point standardPoint(last.getX() + config->getSpeed()*std::cos(utilities::radian(angle)),
                        last.getY() + config->getSpeed()*std::sin(utilities::radian(angle)));

    bool useSecondChoice = ring.containsPoint(mesh.getPoints().getList(),standardPoint);
    int firstNeighbour = -1;

    Point alwaysOutside(last.getX() + ring.getDiameter() * std::cos(utilities::radian(angle)),
                        last.getY() + ring.getDiameter() * std::sin(utilities::radian(angle)));
    Point exitRing;
    IndexSegment intersected = ring.getIntersectedSegment(PointSegment(last, alwaysOutside), exitRing,
                                                          mesh.getPoints().getList());

    Neighbours possibleNeighbours = mesh.getNeighbours(intersected);

    std::vector<Polygon> polygons = {mesh.getPolygon(possibleNeighbours.getFirst()),
                                     mesh.getPolygon(possibleNeighbours.getSecond())};

    int index = -1;
    if (ring.containsPoint(mesh.getPoints().getList(), polygons[0].getCentroid())) {
        firstNeighbour = possibleNeighbours.getSecond();
        index = 1;
    } else {
        if (ring.containsPoint(mesh.getPoints().getList(), polygons[1].getCentroid())) {
            firstNeighbour = possibleNeighbours.getFirst();
            index = 0;
        }
    }

    if(polygons[index].containsPoint(mesh.getPoints().getList(), standardPoint)) {
        useSecondChoice = true;
    }

    if(!useSecondChoice){
       this->tipPoint = standardPoint;
    }else{
        std::vector<int> previous = {possibleNeighbours.getFirst(), possibleNeighbours.getSecond()};
        Point advanceDirection(exitRing.getX() + 2*polygons[index].getDiameter() * std::cos(utilities::radian(angle)),
                               exitRing.getY() + 2*polygons[index].getDiameter() * std::sin(utilities::radian(angle)));

        NeighbourInfo finalPolygonInfo = mesh.getNeighbour(firstNeighbour, PointSegment(last, advanceDirection), previous);
        Polygon finalPolygon = mesh.getPolygon(finalPolygonInfo.neighbour);

        Point finalPoint(finalPolygonInfo.intersection.getX() + finalPolygon.getDiameter()/2 * std::cos(utilities::radian(angle)),
                         finalPolygonInfo.intersection.getY() + finalPolygon.getDiameter()/2 * std::sin(utilities::radian(angle)));
        this->tipPoint = finalPoint;
    }
}

CrackTip::CrackTip(const CrackTip &t) {
    this->points = t.points;
    this->container_polygon = t.container_polygon;
    this->crackAngle = t.crackAngle;
    this->tipPoint = t.tipPoint;
    this->hasFinished = t.hasFinished;
    this->usedRadius = t.usedRadius;
    this->tipTriangles = t.tipTriangles;
    this->ring = t.ring;
}

double CrackTip::calculateAngle(Problem problem, Eigen::VectorXd u) {
    Material m = problem.veamer->getMaterial();
    Pair<int> dofB = problem.veamer->pointToDOFS(this->points.b);
    Pair<int> dofC = problem.veamer->pointToDOFS(this->points.c);
    Pair<int> dofD = problem.veamer->pointToDOFS(this->points.d);
    Pair<int> dofE = problem.veamer->pointToDOFS(this->points.e);

    double factor = (m.E()*std::sqrt(2*M_PI/this->usedRadius)) / (3*(1 + m.v())*(1 + m.k()));

    double kI = factor * (4*(u[dofB.second] - u[dofD.second]) - (u[dofC.second] - u[dofE.second])/2)*std::cos(utilities::radian(this->crackAngle));
    double kII = factor * (4*(u[dofB.first] - u[dofD.first]) - (u[dofC.first] - u[dofE.first])/2)*std::cos(utilities::radian(this->crackAngle));

    if(kII!=0){
        double r = kI/kII;

        return utilities::degrees(2*std::atan(r/4 - utilities::sign(kII)/4*std::sqrt((std::pow(r,2) + 8))))
               + this->crackAngle;
    }else{
        return this->crackAngle + 90;
    }
}

PolygonChangeData CrackTip::grow(Eigen::VectorXd u, Problem problem) {
    double angle = calculateAngle(problem, u);
    Point lastPoint = this->getPoint();

    addPointToPath(angle, *problem.mesh);

    reassignContainer(*problem.mesh);
    problem.mesh->printInFile("changed.txt");
    PointSegment direction(lastPoint, this->getPoint());

    std::vector<int> previous;
    int startTriangleIndex = problem.mesh->getNeighbourFromCommonVertexSet(direction, this->tipTriangles,
                                                                           this->points.center, previous, Polygon());
    UniqueList<int> newPoints;
    PolygonChangeData changeData = problem.mesh->breakMesh(startTriangleIndex, direction, true, newPoints);

    checkIfFinished(problem, direction);

    return changeData;
}

PolygonChangeData CrackTip::prepareTip(BreakableMesh &mesh, double StandardRadius, std::vector<int> entryToContainer) {
    std::vector<int> indexes;
    std::vector<Polygon> oldPolygons;
    std::vector<Polygon> newPolygons;
    std::vector<PointSegment> restricted;

    Polygon poly = mesh.getPolygon(this->container_polygon);

    FractureConfig* config = FractureConfig::instance();

    if(fitsBox(StandardRadius, poly, mesh.getPoints().getList())){
        oldPolygons.push_back(poly);
        restricted.push_back(PointSegment(this->getPoint(), mesh.getPoint(entryToContainer[0])));

        remeshAndAdapt(StandardRadius, newPolygons, this->container_polygon, mesh, std::vector<int>(), restricted);
    } else{
        double candidateRadius = poly.getDiameter()*config->getRatio();

        if(fitsBox(candidateRadius, poly, mesh.getPoints().getList())){
            oldPolygons.push_back(poly);
            restricted.push_back(PointSegment(this->getPoint(), mesh.getPoint(entryToContainer[0])));

            remeshAndAdapt(candidateRadius, newPolygons, this->container_polygon, mesh, std::vector<int>(), restricted);
        } else{
            std::vector<int> unusedPoints;
            int ringIndex = this->getRingPolygon(mesh, unusedPoints, oldPolygons);
            Polygon ringRegion = mesh.getPolygon(ringIndex);
            
            Point last = getPoint();
            BoundingBox box(Point(last.getX()-candidateRadius, last.getY()-candidateRadius),
                            Point(last.getX()+candidateRadius, last.getY()+candidateRadius));

            if (box.fitsInsidePolygon(ringRegion, mesh.getPoints().getList())) {
                restricted.push_back(PointSegment(this->getPoint(), mesh.getPoint(entryToContainer[0])));
                restricted.push_back(PointSegment(mesh.getPoint(entryToContainer[0]), mesh.getPoint(entryToContainer[1])));

                remeshAndAdapt(candidateRadius, newPolygons, ringIndex, mesh, unusedPoints, restricted);
            } else {
                double radius = candidateRadius;
                while(!box.fitsInsidePolygon(ringRegion, mesh.getPoints().getList())) {
                    radius = config->getRatio()*radius;
                    box = BoundingBox(Point(last.getX()-radius, last.getY()-radius),
                                      Point(last.getX()+radius, last.getY()+radius));
                }

                restricted.push_back(PointSegment(this->getPoint(), mesh.getPoint(entryToContainer[0])));
                restricted.push_back(PointSegment(mesh.getPoint(entryToContainer[0]), mesh.getPoint(entryToContainer[1])));

                remeshAndAdapt(radius, newPolygons, ringIndex, mesh, unusedPoints, restricted);
            }
        }
    }

    return PolygonChangeData(oldPolygons, newPolygons);
}

void CrackTip::remeshAndAdapt(double radius, std::vector<Polygon> &newPolygons, int region, BreakableMesh &mesh,
                              std::vector<int> oldPoints, std::vector<PointSegment> restrictedSegments) {
    this->tipTriangles.clear();
    this->crackAngle = restrictedSegments[0].cartesianAngle();
    FractureConfig* config = FractureConfig::instance();

    this->usedRadius = radius;
    RosetteGroupGenerator generator(this->getPoint(), config->getRosetteAngle(),radius);
    std::vector<Point> pointsOnSegment = generator.generatePoints(this->crackAngle);
    std::vector<Point> points = generator.getPoints();

    for (int i : oldPoints) {
        points.push_back(mesh.getPoint(i));
    }

    RemeshAdapter remesher(mesh.getPolygon(region), region);
    this->ring = remesher.getRegion();

    int j = restrictedSegments.size()-1;
    while(pointsOnSegment.size()>0){
        Point p = pointsOnSegment.back();

        PointSegment s = restrictedSegments[j];
        while(!s.splitSegment(p, restrictedSegments)){
            s = restrictedSegments[j];
            if(j<0){
                j = restrictedSegments.size();
            }

            j--;

        }

        restrictedSegments.erase(std::remove(restrictedSegments.begin(), restrictedSegments.end(), s), restrictedSegments.end());
        pointsOnSegment.erase(std::remove(pointsOnSegment.begin(), pointsOnSegment.end(), p), pointsOnSegment.end());
        j = restrictedSegments.size()-1;
    }

    Triangulation t = remesher.triangulate(points, mesh.getPoints().getList(), restrictedSegments);
    std::unordered_map<int,int> pointMap = remesher.includeNewPoints(mesh.getPoints(), t);

    mesh.printInFile("beforeAdapt.txt");
    this->points = CrackTipPoints(pointMap[0], pointMap[1], pointMap[2], pointMap[3], pointMap[4]);

    remesher.adaptToMesh(t, mesh, pointMap, this->tipTriangles, newPolygons);
}

bool CrackTip::isFinished() {
    return this->hasFinished;
}

void CrackTip::assignLocation(int polygon) {
    this->container_polygon = polygon;
}

Point CrackTip::getPoint() {
    return this->tipPoint;
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
    int isOutside = problem.mesh->findContainerPolygon(this->getPoint(), last);
    if(isOutside==-1) {
        Polygon& poly = problem.mesh->getPolygon(last);

        std::vector<IndexSegment> polySeg;
        poly.getSegments(polySeg);

        for (int j = 0; j < polySeg.size() ; ++j) {
            Point p;
            bool intersects = polySeg[j].intersection(problem.mesh->getPoints().getList(), direction, p);

            if(intersects){
                hasFinished = true;
                tipPoint  = p;
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

int CrackTip::getRingPolygon(BreakableMesh &mesh, std::vector<int> &unusedPoints, std::vector<Polygon> &oldPolygons) {
    UniqueList<int> neighbours;
    mesh.getDirectNeighbours(this->container_polygon, neighbours);
    for(int n: neighbours.getList()){
        oldPolygons.push_back(mesh.getPolygon(n));
    }

    return this->getRingPolygon(mesh, unusedPoints, neighbours);
}

int CrackTip::getRingPolygon(BreakableMesh &mesh, std::vector<int> &unusedPoints, UniqueList<int> neighbours) {
    std::vector<int> mergedPoints;
    std::vector<int> ringPolygonPoints = mesh.getAllPoints(neighbours.getList());
    RemeshAdapter remesher(neighbours.getList(), mesh.getPoints().getList(), mesh, mergedPoints);

    Polygon ringRegion = remesher.getRegion();

    unusedPoints = mesh.getUnusedPoints(ringPolygonPoints, mergedPoints);

    mesh.printInFile("afterFirst.txt");
    return remesher.getRegionIndex();
}
