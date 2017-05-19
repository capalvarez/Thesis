#include <fracture/crack/CrackTip.h>
#include <fracture/geometry/mesh/RemeshAdapter.h>
#include <fracture/config/FractureConfig.h>

CrackTip::CrackTip() {}

CrackTip::CrackTip(Point crack) {
    this->tipPoint = crack;
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

void CrackTip::addPointToPath(double angle, BreakableMesh mesh) {
    FractureConfig* config = FractureConfig::instance();
    Point last = mesh.getPoint(points.center);

    Point standardPoint(last.getX() + config->getSpeed()*std::cos(utilities::radian(angle)),
                        last.getY() + config->getSpeed()*std::sin(utilities::radian(angle)));

    bool useSecondChoice = std::abs(standardPoint.distance(last)) < usedRadius;

    Point alwaysOutside(last.getX() + ring.getDiameter() * std::cos(utilities::radian(angle)),
                        last.getY() + ring.getDiameter() * std::sin(utilities::radian(angle)));
    Point exitRing;
    IndexSegment intersected = ring.getIntersectedSegment(PointSegment(last, alwaysOutside), exitRing,
                                                          mesh.getPoints().getList());

    Neighbours possibleNeighbours = mesh.getNeighbours(intersected);
    std::vector<Polygon> polygons;
    int index = -1, otherIndex = -1;
    bool border = false;

    if(possibleNeighbours.isNeighbour(-1)){
        int notNull = possibleNeighbours.getFirst()==-1? possibleNeighbours.getSecond() : possibleNeighbours.getFirst();
        polygons = {mesh.getPolygon(notNull)};
        otherIndex = 0;
        index = 0;
        border = true;
    }else{
        polygons = {mesh.getPolygon(possibleNeighbours.getFirst()), mesh.getPolygon(possibleNeighbours.getSecond())};

        if (ring.containsPoint(mesh.getPoints().getList(), polygons[1].getCentroid())) {
            otherIndex = 0;
            index = 1;
        } else {
            if (ring.containsPoint(mesh.getPoints().getList(), polygons[0].getCentroid())) {
                otherIndex = 1;
                index = 0;
            }
        }
    }

    if(polygons[index].containsPoint(mesh.getPoints().getList(), standardPoint)) {
        useSecondChoice = true;
    }

    if(!useSecondChoice){
       this->tipPoint = standardPoint;
    }else{
        this->tipPoint = this->generateNextPoint(polygons[otherIndex], exitRing, angle, mesh.getPoints().getList(), border);
    }
}

Point
CrackTip::generateNextPoint(Polygon poly, Point intersection, double angle, std::vector<Point> points, bool border) {
    if(border){
        return intersection;
    }

    double length = poly.getDiameter()/2;
    Point finalPoint(intersection.getX() + length * std::cos(utilities::radian(angle)),
                     intersection.getY() + length * std::sin(utilities::radian(angle)));
    while(!poly.containsPoint(points, finalPoint)){
        length = length/2;
        finalPoint = Point(intersection.getX() + length * std::cos(utilities::radian(angle)),
                           intersection.getY() + length * std::sin(utilities::radian(angle)));
    }

    return finalPoint;
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
        double theta1 = 2*atan((r + std::sqrt((std::pow(r,2) + 8)))/4);
        double theta2 = 2*atan((r - std::sqrt((std::pow(r,2) + 8)))/4);

        double t1 = utilities::degrees(theta1);
        double t2 = utilities::degrees(theta2);

        if(theta1*kII<0){
            return utilities::degrees(theta1) + this->crackAngle;
        }else{
            return utilities::degrees(theta2) + this->crackAngle;
        }
    }else{
        return this->crackAngle + 90;
    }
}

PolygonChangeData CrackTip::grow(Eigen::VectorXd u, Problem problem, UniqueList<Pair<int>> &newPoints) {
    double angle = calculateAngle(problem, u);
    Point lastPoint = problem.mesh->getPoint(points.center);

    addPointToPath(angle, *problem.mesh);

    reassignContainer(*problem.mesh);
    PointSegment direction(lastPoint, this->getPoint());

    problem.mesh->printInFile("changed.txt");
    std::vector<int> previous;
    int startTriangleIndex = problem.mesh->getNeighbourFromCommonVertexSet(direction, this->tipTriangles);

    PolygonChangeData changeData = problem.mesh->breakMesh(startTriangleIndex, direction, true, newPoints, previous);
    newPoints.pop_front();

    checkIfFinished(problem, direction);

    return changeData;
}

PolygonChangeData CrackTip::prepareTip(BreakableMesh &mesh, double StandardRadius, std::vector<Pair<int>> previousCrackPoints) {
    std::vector<int> indexes;
    std::vector<Polygon> oldPolygons;
    std::vector<Polygon> newPolygons;

    Polygon poly = mesh.getPolygon(this->container_polygon);
    double angle = PointSegment(mesh.getPoint(previousCrackPoints[0].first),this->tipPoint).cartesianAngle();

    FractureConfig* config = FractureConfig::instance();

    if(fitsBox(StandardRadius, poly, mesh.getPoints().getList())){
        oldPolygons.push_back(poly);

        mesh.getPolygon(this->container_polygon).fixSegment(previousCrackPoints[0], -1);

        IndexSegment crackEntry = mesh.getPolygon(this->container_polygon).getSurroundingVertices(previousCrackPoints[0]);
        remeshAndAdapt(StandardRadius, newPolygons, this->container_polygon, mesh, std::vector<int>(), angle,
                       crackEntry, std::vector<Pair<int>>());
    } else{
        double candidateRadius = poly.getDiameter()*config->getRatio();

        if(fitsBox(candidateRadius, poly, mesh.getPoints().getList())){
            oldPolygons.push_back(poly);

            IndexSegment crackEntry = mesh.getPolygon(this->container_polygon).getSurroundingVertices(previousCrackPoints[0]);
            remeshAndAdapt(candidateRadius, newPolygons, this->container_polygon, mesh, std::vector<int>(), angle,
                           crackEntry, std::vector<Pair<int>>());
        } else{
            std::vector<int> unusedPoints;
            int ringIndex = this->getRingPolygon(mesh, unusedPoints, oldPolygons);
            Polygon ringRegion = mesh.getPolygon(ringIndex);
            ringRegion.fixSegment(previousCrackPoints[1], previousCrackPoints[0].first);
            std::vector<IndexSegment> toErase = ringRegion.deleteVerticesInRange(previousCrackPoints[1].first, previousCrackPoints[1].second);
            SegmentMap& edges = mesh.getSegments();

            for (IndexSegment s: toErase){
                edges.delete_element(s);
            }

            IndexSegment crackEntry = ringRegion.getSurroundingVertices(previousCrackPoints[1]);
            
            Point last = getPoint();
            BoundingBox box(Point(last.getX()-candidateRadius, last.getY()-candidateRadius),
                            Point(last.getX()+candidateRadius, last.getY()+candidateRadius));

            if (box.fitsInsidePolygon(ringRegion, mesh.getPoints().getList())) {
                remeshAndAdapt(candidateRadius, newPolygons, ringIndex, mesh, unusedPoints, angle, crackEntry,
                               std::vector<Pair<int>>());
            } else {
                double radius = candidateRadius;
                while(!box.fitsInsidePolygon(ringRegion, mesh.getPoints().getList())) {
                    radius = config->getRatio()*radius;
                    box = BoundingBox(Point(last.getX()-radius, last.getY()-radius),
                                      Point(last.getX()+radius, last.getY()+radius));
                }

                ringRegion.fixSegment(previousCrackPoints[1], previousCrackPoints[0].first);
                remeshAndAdapt(radius, newPolygons, ringIndex, mesh, unusedPoints, angle, crackEntry,
                               std::vector<Pair<int>>());
            }
        }
    }

    return PolygonChangeData(oldPolygons, newPolygons);
}

void CrackTip::remeshAndAdapt(double radius, std::vector<Polygon> &newPolygons, int region, BreakableMesh &mesh,
                              std::vector<int> oldPoints, double angle, IndexSegment crackEntry,
                              std::vector<Pair<int>> previousCrackPoints) {
    this->tipTriangles.clear();
    this->crackAngle = angle;
    UniqueList<Point>& meshPoints = mesh.getPoints();
    FractureConfig* config = FractureConfig::instance();

    this->usedRadius = radius;
    QuarterPointElementsGenerator generator(this->getPoint(), config->getRosetteAngle(),radius);
    generator.generateGroup(this->crackAngle);
    std::vector<Point> rosettePoints = generator.getPoints();

    std::vector<Point> toTriangulate;
    for (int i : oldPoints) {
        toTriangulate.push_back(mesh.getPoint(i));
    }

    RemeshAdapter remesher;
    std::unordered_map<int,int> pointMap = remesher.includeNewPoints(meshPoints, rosettePoints);
    mesh.printInFile("beforeAdapting.txt");

    meshPoints.force_push_back(rosettePoints[rosettePoints.size()-2]);
    meshPoints.force_push_back(rosettePoints[rosettePoints.size()-1]);
    pointMap[rosettePoints.size()-2] = meshPoints.size()-2;
    pointMap[rosettePoints.size()-1] = meshPoints.size()-1;

    Polygon ring = Polygon(mesh.getPolygon(region));

    std::vector<int> quarterTipBorder;
    for (int i: generator.getBorderPoints()){
        quarterTipBorder.push_back(pointMap[i]);
    }

    ring.replaceSegment(crackEntry, quarterTipBorder);
    std::vector<int> newPolygonPoints = {crackEntry.getFirst(), previousCrackPoints[0].first,
                                         previousCrackPoints[0].second, crackEntry.getSecond(), quarterTipBorder.back(),
                                         pointMap[2], meshPoints.size()-1, quarterTipBorder[0]};
    Polygon otherPolygon = Polygon(newPolygonPoints, meshPoints.getList());
    mesh.getPolygons().push_back(otherPolygon);
    int otherPolygon_index = mesh.getPolygons().size() - 1;

    SegmentMap& edges = mesh.getSegments();
    std::vector<IndexSegment> otherPolygonSegments;
    otherPolygon.getSegments(otherPolygonSegments);

    int j;
    for (j = 0; j < 3; ++j) {
        edges.replace_neighbour(otherPolygonSegments[j], region, otherPolygon_index);
    }

    for(j = 3; j<otherPolygonSegments.size(); j++){
        edges.insert(otherPolygonSegments[j], Neighbours(otherPolygon_index, region));
    }

    mesh.replacePolygon(region, ring);

    std::vector<int> firstAndLast = {mesh.getPolygons().size()};
    remesher.adaptPolygonsToMesh(generator.getElements(), mesh, pointMap, newPolygons);
    firstAndLast.push_back(mesh.getPolygons().size()-1);

    this->points = CrackTipPoints(pointMap[0], meshPoints.size()-2, meshPoints.size()-1, pointMap[1], pointMap[2]);

    mesh.printInFile("beforeAdapting.txt");
    mesh.getSegments().printInFile("segments.txt");

    remesher = RemeshAdapter(mesh.getPolygon(region), region);
    this->ring = remesher.getRegion();

    Triangulation t = remesher.triangulate(toTriangulate, meshPoints.getList());
    pointMap = remesher.includeNewPoints(meshPoints, t);

    remesher.adaptTriangulationToMesh(t, mesh, pointMap, this->tipTriangles, newPolygons);
    mesh.printInFile("afterAdapting.txt");
    mesh.getSegments().printInFile("segments.txt");

    std::vector<int> crackPolygon1Points, crackPolygon2Points;
    bool include = false;
    if(previousCrackPoints.size()>1){
        include = otherPolygon.containsPoint(meshPoints.getList(), mesh.getPoint(previousCrackPoints[1].first));

        if(include){
            crackPolygon1Points.push_back(previousCrackPoints[1].first);
            crackPolygon2Points.push_back(previousCrackPoints[1].second);
        }
    }

    crackPolygon1Points.push_back(previousCrackPoints[0].second);
    crackPolygon1Points.push_back(crackEntry.getSecond());
    crackPolygon1Points.push_back(quarterTipBorder.back());
    crackPolygon1Points.push_back(newPolygonPoints[5]);

    crackPolygon2Points.push_back(meshPoints.size()-1);
    crackPolygon2Points.push_back(quarterTipBorder[0]);
    crackPolygon2Points.push_back(crackEntry.getFirst());
    crackPolygon2Points.push_back(previousCrackPoints[0].first);

    Polygon crackPolygon1 = Polygon(crackPolygon1Points, meshPoints.getList());
    Polygon crackPolygon2 = Polygon(crackPolygon2Points, meshPoints.getList());

    mesh.replacePolygon(otherPolygon_index, crackPolygon1);
    mesh.getPolygons().push_back(crackPolygon2);
    int crackPolygon2_index = mesh.getPolygons().size() - 1;

    std::vector<IndexSegment> crackPolygon1Segments, crackPolygon2Segments;
    crackPolygon1.getSegments(crackPolygon1Segments);
    crackPolygon2.getSegments(crackPolygon2Segments);

    edges.insert(crackPolygon1Segments.back(),Neighbours(otherPolygon_index,-1));
    edges.insert(crackPolygon2Segments.back(),Neighbours(otherPolygon_index,-1));
    if(previousCrackPoints.size()>1 && include){
        edges.insert(crackPolygon1Segments[0],Neighbours(otherPolygon_index,-1));
        edges.insert(crackPolygon2Segments[0],Neighbours(otherPolygon_index,-1));
    }

    for (int i = 0; i < crackPolygon1Segments.size() ; ++i) {
        edges.replace_neighbour(crackPolygon1Segments[i], otherPolygon_index, otherPolygon_index);
    }

    for (int i = 0; i < crackPolygon2Segments.size() ; ++i) {
        edges.replace_neighbour(crackPolygon2Segments[i], otherPolygon_index, crackPolygon2_index);
    }

    if(previousCrackPoints.size() && !include){
        mesh.getPolygon(firstAndLast[0]).insertVertex(previousCrackPoints[1].first, meshPoints.getList());
        mesh.getPolygon(firstAndLast[1]).insertVertex(previousCrackPoints[1].second, meshPoints.getList());
    }


    mesh.printInFile("afterAdapting.txt");
    mesh.getSegments().printInFile("segments.txt");
    newPolygons.push_back(crackPolygon1);
    newPolygons.push_back(crackPolygon2);
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
            mesh.getNeighboursByPoint(container, neighbours);

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
    mesh.getNeighboursByPoint(this->container_polygon, neighbours);
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

