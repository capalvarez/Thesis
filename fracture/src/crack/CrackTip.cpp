#include <fracture/crack/CrackTip.h>
#include <fracture/geometry/mesh/RemeshAdapter.h>
#include <fracture/config/FractureConfig.h>
#include <fracture/utilities/greater.h>

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

    bool useSecondChoice = std::abs(standardPoint.distance(last)) < usedRadius/config->getRatio();

    if(!useSecondChoice){
        this->tipPoint = standardPoint;
    }else{
        this->tipPoint = Point (last.getX() + 2*(usedRadius/std::pow(config->getRatio(),2))*std::cos(utilities::radian(angle)),
                                last.getY() + 2*(usedRadius/std::pow(config->getRatio(),2))*std::sin(utilities::radian(angle)));
    }
}

double CrackTip::calculateAngle(Problem problem, Eigen::VectorXd u) {
    Material m = problem.veamer->getMaterial();
    Pair<int> dofB = problem.veamer->pointToDOFS(this->points.b);
    Pair<int> dofC = problem.veamer->pointToDOFS(this->points.c);
    Pair<int> dofD = problem.veamer->pointToDOFS(this->points.d);
    Pair<int> dofE = problem.veamer->pointToDOFS(this->points.e);

    double factor = (m.E()*std::sqrt(M_PI/(2*this->usedRadius))/((1 + m.v())*(1 + m.k())));

    Pair<double> dPB = changeCoordinateSystem(u[dofB.first], u[dofB.second]);
    Pair<double> dPC = changeCoordinateSystem(u[dofC.first], u[dofC.second]);
    Pair<double> dPD = changeCoordinateSystem(u[dofD.first], u[dofD.second]);
    Pair<double> dPE = changeCoordinateSystem(u[dofE.first], u[dofE.second]);

    double kI = factor * (4*(dPB.second - dPD.second) - (dPC.second - dPE.second));
    double kII = factor * (4*(dPB.first - dPD.first) - (dPC.first - dPE.first));

    if(kII!=0){
        double r = kI/kII;
        double theta = 2*atan((r - utilities::sign(kII)*std::sqrt((std::pow(r,2) + 8)))/4);

        return this->crackAngle + utilities::degrees(theta);
    }else{
        return this->crackAngle + 90;
    }
}

Pair<double> CrackTip::changeCoordinateSystem(double dX, double dY) {
    double crackRadian = utilities::radian(crackAngle);

    double magnitude = xpoly_utilities::norm(Point(dX, dY));
    double alpha = atan2(dY, dX);
    double diff = std::abs(crackRadian - alpha);

    return Pair<double>(magnitude*std::cos(diff), magnitude*std::sin(diff));
}

PolygonChangeData CrackTip::grow(Eigen::VectorXd u, Problem problem, UniqueList<Pair<int>> &newPoints, PointSegment previousCrackSegment) {
    std::vector<Polygon> newPolygons;
    std::vector<Polygon> oldPolygons;

    problem.mesh->getSegments().printInFile("segmentsBeforeReassign.txt");
    double angle = calculateAngle(problem, u);
    Point lastPoint = problem.mesh->getPoint(points.center);

    addPointToPath(angle, *problem.mesh);

    reassignContainer(*problem.mesh);

    problem.mesh->getSegments().printInFile("segmentsAfterReassign.txt");
    PointSegment direction(lastPoint, this->getPoint());

    problem.mesh->printInFile("changed.txt");
    UniqueList<Point>& meshPoints = problem.mesh->getPoints();
    SegmentMap& edges = problem.mesh->getSegments();
    NeighbourInfo n2;

    int startTriangleIndex = problem.mesh->getNeighbourFromCommonVertexSet(direction, this->tipTriangles, n2);
    IndexSegment containerSegment = problem.mesh->getPolygon(startTriangleIndex).containerEdge(meshPoints.getList(), lastPoint);
    NeighbourInfo n1 = NeighbourInfo(startTriangleIndex, containerSegment, lastPoint, false);
    n1.isVertex = true;

    int duplicatedCenter = meshPoints.force_push_back(lastPoint);

    int p1 = meshPoints.push_back(n2.intersection);
    int p2 = meshPoints.force_push_back(n2.intersection);

    Pair<int> newCrackPoints1(this->points.center,duplicatedCenter);
    Pair<int> newCrackPoints2(p1,p2);

    newPoints.push_back(newCrackPoints1);
    newPoints.push_back(newCrackPoints2);

    std::vector<int> new1 = {points.center, p1};
    std::vector<int> new2 = {p2, points.center};

    Polygon& other = problem.mesh->getPolygon(startTriangleIndex);
    Pair<int> pairs = problem.mesh->computeNewPolygons(n1, n2, other, newPolygons, new1, new2, new1[0], new1[1], -1, p1, p2);
    tipTriangles.push_back(pairs.second);
    Polygon polygon1 = problem.mesh->getPolygon(pairs.first);
    Polygon polygon2 = problem.mesh->getPolygon(pairs.second);

    std::vector<IndexSegment> polygon1Segments, polygon2Segments;
    polygon1.getSegments(polygon1Segments);
    polygon2.getSegments(polygon2Segments);

    for (int i = 0; i < polygon1Segments.size() ; ++i) {
        edges.replace_neighbour(polygon1Segments[i], n1.neighbour, pairs.first);
    }

    for (int i = 0; i < polygon2Segments.size() ; ++i) {
        edges.replace_neighbour(polygon2Segments[i], n1.neighbour, pairs.second);
    }

    Polygon& nextNeighbour = problem.mesh->getPolygon(n2.neighbour);
    nextNeighbour.insertOnSegment(n2.edge, {p1,p2});

    edges.insert(IndexSegment(p1,p2), Neighbours(n2.neighbour,-1));
    edges.insert(IndexSegment(n2.edge.getSecond(),p1), n2.neighbour);
    edges.insert(IndexSegment(n2.edge.getFirst(),p2), n2.neighbour);

    problem.mesh->printInFile("afterFirstBreak.txt");

    edges.printInFile("beforeDeleting.txt");

    for (int t: this->tipTriangles) {
        Polygon& polygon = problem.mesh->getPolygon(t);

        if(fracture_utilities::orientation(previousCrackSegment, polygon.getCentroid())<0 &&
           fracture_utilities::orientation(direction, polygon.getCentroid())<0){
            polygon.replaceVertex(points.center, duplicatedCenter, edges);
        }
    }

    std::vector<int> previous = {pairs.first, pairs.second};
    PolygonChangeData changeData = problem.mesh->breakMesh(n1.neighbour, direction, false, newPoints, previous,
                                                           this->previouslyBroken, this->mergedBroken);

    problem.mesh->printInFile("afterSecondBreak.txt");
    checkIfFinished(problem, direction);

    return changeData;
}

std::vector<Pair<int>> CrackTip::prepareTip(BreakableMesh &mesh, double StandardRadius, std::vector<Pair<int>> previousCrackPoints,
                                            std::vector<Polygon> &oldPolygons, std::vector<Polygon> &newPolygons) {
    std::vector<int> indexes;
    std::vector<Pair<int>> newCrackPoints;

    Polygon poly = mesh.getPolygon(this->container_polygon);
    double angle = PointSegment(mesh.getPoint(previousCrackPoints[0].first),this->tipPoint).cartesianAngle();

    FractureConfig* config = FractureConfig::instance();

    if(fitsBox(StandardRadius, poly, mesh.getPoints().getList())){
        oldPolygons.push_back(poly);
        mesh.getPolygon(this->container_polygon).fixSegment(previousCrackPoints[0], -1);

        IndexSegment crackEntry = mesh.getPolygon(this->container_polygon).getSurroundingVertices(
                previousCrackPoints[0], mesh.getPoints().getList());
        newCrackPoints = remeshAndAdapt(StandardRadius, newPolygons, this->container_polygon, mesh, std::vector<int>(), angle,
                       crackEntry, {previousCrackPoints[0]});
    } else{
        double secondRadius = StandardRadius*config->getRatio();

        if(fitsBox(secondRadius, poly, mesh.getPoints().getList())){
            oldPolygons.push_back(poly);

            IndexSegment crackEntry = mesh.getPolygon(this->container_polygon).getSurroundingVertices(previousCrackPoints[0],
                                                                                                      mesh.getPoints().getList());
            newCrackPoints = remeshAndAdapt(secondRadius, newPolygons, this->container_polygon, mesh, std::vector<int>(), angle,
                           crackEntry, {previousCrackPoints[0]});
        } else{
            std::vector<int> unusedPoints;
            int ringIndex = this->getRingPolygon(mesh, unusedPoints, oldPolygons);
            this->container_polygon = ringIndex;
            Polygon& ringRegion = mesh.getPolygon(ringIndex);
            ringRegion.fixSegment(previousCrackPoints[1], previousCrackPoints[0].first);

            mesh.printInFile("afterMerging.txt");
            std::vector<IndexSegment> toErase = ringRegion.deleteVerticesInRange(previousCrackPoints[1].first, previousCrackPoints[1].second);
            mesh.printInFile("afterDeleting.txt");

            Point last = getPoint();
            BoundingBox box(Point(last.getX()-secondRadius, last.getY()-secondRadius),
                            Point(last.getX()+secondRadius, last.getY()+secondRadius));

            int i = 1;
            while (!box.fitsInsidePolygon(mesh.getPolygon(ringIndex), mesh.getPoints().getList())) {
                ringIndex = this->getRingPolygon(mesh, unusedPoints, oldPolygons);
                this->container_polygon = ringIndex;
                mesh.printInFile("afterMerging.txt");
                Polygon& ringRegion = mesh.getPolygon(ringIndex);
                ringRegion.fixSegment(previousCrackPoints[i+1], previousCrackPoints[i].first);

                toErase = ringRegion.deleteVerticesInRange(previousCrackPoints[i+1].first, previousCrackPoints[i+1].second);
                mesh.printInFile("afterDeleting.txt");
                i++;
            }

            SegmentMap& edges = mesh.getSegments();

            for (IndexSegment s: toErase){
                edges.delete_element(s);
            }

            IndexSegment crackEntry = ringRegion.getSurroundingVertices(previousCrackPoints[1], mesh.getPoints().getList());


            std::vector<Pair<int>> relevantCrackPoints(previousCrackPoints.begin(), previousCrackPoints.begin()+i+1);
            newCrackPoints = remeshAndAdapt(secondRadius, newPolygons, ringIndex, mesh, unusedPoints, angle, crackEntry,
                                            relevantCrackPoints);
        }
    }

    return newCrackPoints;
}

std::vector<Pair<int>> CrackTip::remeshAndAdapt(double radius, std::vector<Polygon> &newPolygons, int region,
                                                BreakableMesh &mesh, std::vector<int> oldPoints, double angle,
                                                IndexSegment crackEntry, std::vector<Pair<int>> previousCrackPoints) {
    this->tipTriangles.clear();
    this->crackAngle = angle;
    UniqueList<Point>& meshPoints = mesh.getPoints();
    FractureConfig* config = FractureConfig::instance();

    this->usedRadius = radius;
    QuarterPointElementsGenerator generator(this->getPoint(), config->getRosetteAngle(),radius);
    generator.generateGroup(this->crackAngle);
    std::vector<Point> rosettePoints = generator.getPoints();

    std::vector<Point> toTriangulate;
    std::unordered_map<int,int> ringMap;
    for (int i : oldPoints) {
        ringMap[i] = 0;
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
    for (int i: ring.getPoints()){
        ringMap[i] = 0;
    }

    std::vector<int> quarterTipBorder;
    for (int i: generator.getBorderPoints()){
        quarterTipBorder.push_back(pointMap[i]);
    }

    std::vector<int> newPolygonPoints = ring.getVerticesInRange(crackEntry.getFirst(), crackEntry.getSecond());
    std::vector<int> closingPoints = {quarterTipBorder.back(), pointMap[2], meshPoints.size()-1, quarterTipBorder[0]};
    newPolygonPoints.insert(newPolygonPoints.end(), closingPoints.begin(), closingPoints.end());
    int firstQuarterPointCrack = pointMap[2], secondQuarterPointCrack = meshPoints.size() -1;
    IndexSegment surroundingCrack = ring.getSurroundingVertices(previousCrackPoints.back());

    ring.replaceSegment(crackEntry, quarterTipBorder);

    Polygon otherPolygon = Polygon(newPolygonPoints, meshPoints.getList());
    mesh.getPolygons().push_back(otherPolygon);
    int otherPolygon_index = mesh.getPolygons().size() - 1;

    SegmentMap& edges = mesh.getSegments();
    Neighbours crackEntryNeighbours1 = edges.get(IndexSegment(surroundingCrack.getFirst(), previousCrackPoints.back().first));
    Neighbours crackEntryNeighbours2 = edges.get(IndexSegment(surroundingCrack.getSecond(), previousCrackPoints.back().second));
    int originalNeighbour1 = crackEntryNeighbours1.getFirst()==region? crackEntryNeighbours1.getSecond() : crackEntryNeighbours1.getFirst();
    int originalNeighbour2 = crackEntryNeighbours2.getFirst()==region? crackEntryNeighbours2.getSecond() : crackEntryNeighbours2.getFirst();

    std::vector<IndexSegment> otherPolygonSegments;
    otherPolygon.getSegments(otherPolygonSegments);

    edges.insert(otherPolygonSegments[0], Neighbours(otherPolygon_index, originalNeighbour1));
    edges.insert(otherPolygonSegments[1], Neighbours(otherPolygon_index, -1));
    edges.insert(otherPolygonSegments[2], Neighbours(otherPolygon_index, originalNeighbour2));

    int j;
    for(j = 3; j<otherPolygonSegments.size(); j++){
        edges.insert(otherPolygonSegments[j], Neighbours(otherPolygon_index, region));
    }

    mesh.replacePolygon(region, ring);

    std::vector<int> firstAndLast = {(int)mesh.getPolygons().size()};
    remesher.adaptPolygonsToMesh(generator.getElements(), mesh, pointMap, newPolygons, this->tipTriangles);
    firstAndLast.push_back(mesh.getPolygons().size()-1);

    if(crackAngle<90 || crackAngle>270){
        this->points = CrackTipPoints(pointMap[0], meshPoints.size()-2, meshPoints.size()-1, pointMap[1], pointMap[2]);
    }else{
        this->points = CrackTipPoints(pointMap[0],  pointMap[1], pointMap[2], meshPoints.size()-2, meshPoints.size()-1);
    }

    mesh.printInFile("beforeAdapting.txt");
    mesh.getSegments().printInFile("segments.txt");

    remesher = RemeshAdapter(mesh.getPolygon(region), region);
    this->ring = remesher.getRegion();

    j = oldPoints.size()-1;
    while(j>=0){
        if(this->ring.containsPoint(meshPoints.getList(), mesh.getPoint(oldPoints[j]))){
            oldPoints.erase(oldPoints.begin()+j);
        }
        j--;
    }

    Triangulation t = remesher.triangulate(toTriangulate, meshPoints.getList());
    pointMap = remesher.includeNewPoints(meshPoints, t);

    mesh.printInFile("afterAdapting.txt");
    remesher.adaptTriangulationToMesh(t, mesh, pointMap, newPolygons, ringMap);
    mesh.printInFile("afterAdapting.txt");
    mesh.getSegments().printInFile("segments.txt");

    NeighbourInfo n1 = NeighbourInfo(otherPolygon_index, IndexSegment(quarterTipBorder.back(), quarterTipBorder[0]), Point(),
                                     false);
    NeighbourInfo n2 = NeighbourInfo(-1, surroundingCrack, Point(),
                                     false);

    std::vector<int> new1 = {firstQuarterPointCrack, previousCrackPoints.back().second};
    std::vector<int> new2 = {previousCrackPoints.back().first, secondQuarterPointCrack};

    std::vector<bool> include(previousCrackPoints.size()-2, false);

    if(previousCrackPoints.size()>1){
        for (int i = 0; i < previousCrackPoints.size()-1; ++i) {
            include[i] = otherPolygon.containsPoint(meshPoints.getList(), mesh.getPoint(previousCrackPoints[i].first));

            if(include[i]){
                new1.insert(new1.begin()+i+1, previousCrackPoints[i].first);
                new2.insert(new2.begin()+i+1, previousCrackPoints[i].second);
            }
        }
    }

    Polygon& other = mesh.getPolygon(otherPolygon_index);
    other.deleteVerticesInRange(surroundingCrack.getFirst(), surroundingCrack.getSecond());
    Pair<int> pairs = mesh.computeNewPolygons(n1, n2,other, newPolygons, new1, new2, new1[0], new1.back(), -1, new2.back(), new2[0]);

    Polygon crackPolygon1 = mesh.getPolygon(pairs.first);
    Polygon crackPolygon2 = mesh.getPolygon(pairs.second);

    j = oldPoints.size()-1;
    while (j>=0){
        if(crackPolygon1.containsPoint(meshPoints.getList(), mesh.getPoint(oldPoints[j]))){
            new1.insert(new1.begin()+1, oldPoints[j]);

        } else{
            if(crackPolygon2.containsPoint(meshPoints.getList(), mesh.getPoint(oldPoints[j]))){

            }
        }

        j--;

    }




    mesh.replacePolygon(otherPolygon_index, crackPolygon1);

    std::vector<IndexSegment> crackPolygon1Segments, crackPolygon2Segments;
    crackPolygon1.getSegments(crackPolygon1Segments);
    crackPolygon2.getSegments(crackPolygon2Segments);

    edges.insert(crackPolygon1Segments[0],Neighbours(otherPolygon_index,-1));
    edges.insert(crackPolygon2Segments[0],Neighbours(otherPolygon_index,-1));

    if(previousCrackPoints.size()>1){
        for (int i = 0; i < previousCrackPoints.size()-1; ++i) {
            if(include[i]){
                edges.insert(crackPolygon1Segments[i+1],Neighbours(otherPolygon_index,-1));
                edges.insert(crackPolygon2Segments[i+1],Neighbours(otherPolygon_index,-1));
            }
        }
    }

    for (int i = 0; i < crackPolygon1Segments.size() ; ++i) {
        edges.replace_neighbour(crackPolygon1Segments[i], otherPolygon_index, otherPolygon_index);
    }

    for (int i = 0; i < crackPolygon2Segments.size() ; ++i) {
        edges.replace_neighbour(crackPolygon2Segments[i], otherPolygon_index, pairs.second);
    }

    if(previousCrackPoints.size()>1){
        for (int i = 0; i < previousCrackPoints.size()-1; ++i) {
            if(!include[i]){
                mesh.getPolygon(firstAndLast[0]).insertVertex(previousCrackPoints[i].first, meshPoints.getList());
                mesh.getPolygon(firstAndLast[1]).insertVertex(previousCrackPoints[i].second, meshPoints.getList());
            }
        }
    }

    mesh.printInFile("afterAdapting.txt");
    mesh.getSegments().printInFile("segmentsAtEnd.txt");
    newPolygons.push_back(crackPolygon1);
    newPolygons.push_back(crackPolygon2);

    Pair<int> outerCrackPoints = Pair<int>(this->points.c, this->points.e);
    Pair<int> innerCrackPoints = Pair<int>(this->points.b, this->points.d);

    return {outerCrackPoints, innerCrackPoints};
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
    if(previouslyBroken.size()>0){
        std::vector<int> neighboursVector = neighbours.getList();

        std::sort(neighboursVector.begin(), neighboursVector.end(), greater());
        std::sort(previouslyBroken.begin(), previouslyBroken.end(), greater());

        std::vector<int> common;
        std::set_intersection(neighboursVector.begin(), neighboursVector.end(), previouslyBroken.begin(), previouslyBroken.end(), std::back_inserter(common));

        if(common.size()>0){
            std::vector<Polygon>& polygons = mesh.getPolygons();
            polygons[previouslyBroken.back()] = mergedBroken;
            mesh.replacePolygonsForMerged(previouslyBroken);
            mesh.getSegments().printInFile("segments.txt");
        }

        neighbours.clear();
        mesh.getNeighboursByPoint(this->container_polygon, neighbours);
    }

    std::vector<int> ringPolygonPoints = mesh.getAllPoints(neighbours.getList());
    RemeshAdapter remesher(neighbours.getList(), mesh.getPoints().getList(), mesh, mergedPoints);

    Polygon ringRegion = remesher.getRegion();

    unusedPoints = mesh.getUnusedPoints(ringPolygonPoints, mergedPoints);

    mesh.printInFile("afterFirst.txt");
    return remesher.getRegionIndex();
}

