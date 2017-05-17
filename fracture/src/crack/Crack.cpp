#include <fracture/crack/Crack.h>
#include <fracture/config/FractureConfig.h>

Crack::Crack() {}

Crack::Crack(Point init, Point end, double speed, double ratio) {
    FractureConfig* config = FractureConfig::instance();
    config->setGrowthSpeed(speed);
    config->setCrackRatio(ratio);

    this->init = CrackTip(init);
    this->end = CrackTip(end);

    this->StandardRadius = config->getDiameterRatio()*PointSegment(init, end).length();
}

Crack::Crack(const Crack& c) {
    this->init = c.init;
    this->end = c.end;
}

Crack::Crack(Point init, Point end) {
    FractureConfig* config = FractureConfig::instance();

    this->init = CrackTip(init);
    this->end = CrackTip(end);

    this->StandardRadius = config->getDiameterRatio()*PointSegment(init, end).length();
}

PolygonChangeData Crack::prepareTip(BreakableMesh &m) {
    FractureConfig* config = FractureConfig::instance();

    UniqueList<Polygon> oldP;
    std::vector<Polygon> newP;
    UniqueList<Point> points = m.getPoints();

    bool bothAreGrowing = !this->init.hasFinished && !this->end.hasFinished;

    if(bothAreGrowing){
        UniqueList<int> initNeighbours;
        UniqueList<int> endNeighbours;

        m.getNeighboursByPoint(this->init.container_polygon, initNeighbours);
        m.getNeighboursByPoint(this->end.container_polygon, endNeighbours);

        if(initNeighbours.hasCommonElement(endNeighbours)){
            initNeighbours.push_list(endNeighbours.getList());

            initNeighbours.push_back(this->init.container_polygon);
            initNeighbours.push_back(this->end.container_polygon);

            for (int n: initNeighbours.getList()){
                oldP.push_back(m.getPolygon(n));
            }

            std::vector<int> allPoints = m.getAllPoints(initNeighbours.getList());
            int index = m.mergePolygons(initNeighbours.getList());
            Polygon ring = m.getPolygon(index);
            std::vector<int> unused = m.getUnusedPoints(allPoints, ring.getPoints());

            double radius = adjustBoxes(ring, ring, points.getList());

            Point init_last = this->init.getPoint();
            BoundingBox init_box(Point(init_last.getX()-radius, init_last.getY()-radius),
                                 Point(init_last.getX()+radius, init_last.getY()+radius));

            Point end_last = this->end.getPoint();
            BoundingBox end_box(Point(end_last.getX()-radius, end_last.getY()-radius),
                                Point(end_last.getX()+radius, end_last.getY()+radius));

            while(init_box.intersects(end_box)){
                radius = config->getRatio()*radius;

                init_box = BoundingBox(Point(init_last.getX()-radius, init_last.getY()-radius),
                                       Point(init_last.getX()+radius, init_last.getY()+radius));
                end_box = BoundingBox(Point(end_last.getX()-radius, end_last.getY()-radius),
                                      Point(end_last.getX()+radius, end_last.getY()+radius));
            }

            Point p1 = end_box.getClosestTo(init_box.centroid());
            Point p2 = init_box.getClosestTo(end_box.centroid());

            Point middle = Point(std::abs(p1.getX()-p2.getX())/2 + std::min(p1.getX(), p2.getX()),
                                 std::abs(p1.getY()-p2.getY())/2 + std::min(p1.getY(), p2.getY()));
            Point nextPoint;

            double dY = (p2.getY() - p1.getY());

            if(dY!=0){
                double slope = -(p2.getX() - p1.getX())/dY;
                nextPoint = Point(middle.getX()*2 , slope*middle.getX() + middle.getY());
            }else{
                nextPoint = Point(middle.getX(), 2*middle.getY());
            }

            PointSegment direction(middle, nextPoint);

            std::vector<Point> intersections;
            std::vector<IndexSegment> relevantSegments;
            std::vector<IndexSegment> segs;
            ring.getSegments(segs);

            for (IndexSegment s: segs) {
                Point p;

                if(direction.intersectionInfinite(points[s.getFirst()], points[s.getSecond()],p)){
                    intersections.push_back(p);
                    relevantSegments.push_back(s);
                }
            }

            SegmentMap e = m.getSegments();
            Neighbours n_f = e.get(relevantSegments[0]);
            int neighbour1 = utilities::indexOf(initNeighbours.getList(), n_f.getFirst())!=-1? n_f.getSecond() : n_f.getFirst();

            Neighbours n_s = e.get(relevantSegments[1]);
            int neighbour2 = utilities::indexOf(initNeighbours.getList(), n_s.getFirst())!=-1? n_s.getSecond() : n_s.getFirst();

            NeighbourInfo n1 = NeighbourInfo(index, relevantSegments[0], intersections[0], false);
            NeighbourInfo n2 = NeighbourInfo(neighbour2, relevantSegments[1], intersections[1], false);

            m.splitPolygons(n1, n2, neighbour1, oldP.getList(), newP);

            int poly1 = m.getPolygon(index).containsPoint(m.getPoints().getList(), this->init.getPoint())?
                        index : (int)(m.getPolygons().size())-1;
            int poly2 = poly1==index? (int)(m.getPolygons().size())-1 : index;

            Point crackPoint;
            PointSegment(intersections[0], intersections[1]).intersection(PointSegment(init_last, end_last), crackPoint);
            crackPath.clear();

            Polygon polygon1 = m.getPolygon(poly1);
            Polygon polygon2 = m.getPolygon(poly2);

            std::vector<int> toPoly1;
            std::vector<int> toPoly2;

            for(int u: unused){
                if(polygon1.containsPoint(points.getList(), m.getPoint(u))){
                    toPoly1.push_back(u);
                } else{
                    toPoly2.push_back(u);
                }
            }

            double angleInit = PointSegment(this->end.tipPoint, this->init.tipPoint).cartesianAngle();
            double angleEnd = PointSegment(this->init.tipPoint, this->end.tipPoint).cartesianAngle();

            IndexSegment crackEntry = polygon1.containerEdge(m.getPoints().getList(), crackPoint);

            this->init.remeshAndAdapt(radius, newP, poly1, m, toPoly1, angleInit, crackEntry, std::vector<Pair<int>>());
            this->end.remeshAndAdapt(radius, newP, poly2, m, toPoly2, angleEnd, crackEntry, std::vector<Pair<int>>());

        }else{
            double radius;
            int initPoly_index, endPoly_index;
            std::vector<int> unusedInit, unusedEnd, affectedPolygons;
            IndexSegment initCrackEntry, endCrackEntry;
            std::vector<Pair<int>> initCrackPoints, endCrackPoints;

            double initAngle = PointSegment(m.getPoint(crackPath.first().first), this->init.tipPoint).cartesianAngle();
            double endAngle = PointSegment(m.getPoint(crackPath.last().first), this->end.tipPoint).cartesianAngle();

            if(this->init.fitsBox(StandardRadius, m.getPolygon(this->init.container_polygon), m.getPoints().getList())
               && this->end.fitsBox(StandardRadius, m.getPolygon(this->end.container_polygon), m.getPoints().getList())){
                radius = StandardRadius;
                initPoly_index = this->init.container_polygon;
                endPoly_index = this->end.container_polygon;

                oldP.push_back(m.getPolygon(initPoly_index));
                oldP.push_back(m.getPolygon(endPoly_index));

                initCrackEntry = m.getPolygon(initPoly_index).getSurroundingVertices(crackPath.first());
                endCrackEntry = m.getPolygon(endPoly_index).getSurroundingVertices(crackPath.last());

                initCrackPoints = {crackPath.first()};
                endCrackPoints = {crackPath.last()};
            } else {
                if(this->init.fitsBox(StandardRadius*config->getRatio(), m.getPolygon(this->init.container_polygon), m.getPoints().getList())
                   && this->end.fitsBox(StandardRadius*config->getRatio(), m.getPolygon(this->end.container_polygon), m.getPoints().getList())){
                    radius = StandardRadius*config->getRatio();
                    initPoly_index = this->init.container_polygon;
                    endPoly_index = this->end.container_polygon;

                    oldP.push_back(m.getPolygon(initPoly_index));
                    oldP.push_back(m.getPolygon(endPoly_index));

                    initCrackEntry = m.getPolygon(initPoly_index).getSurroundingVertices(crackPath.first());
                    endCrackEntry = m.getPolygon(endPoly_index).getSurroundingVertices(crackPath.last());

                    initCrackPoints = {crackPath.first()};
                    endCrackPoints = {crackPath.last()};
                }else{
                    for (int i: initNeighbours.getList()){
                        oldP.push_back(m.getPolygon(i));
                    }

                    for (int i: endNeighbours.getList()){
                        oldP.push_back(m.getPolygon(i));
                    }

                    initPoly_index = this->init.getRingPolygon(m, unusedInit, initNeighbours);
                    m.printInFile("afterMergingFirst.txt");
                    //We have changed the mesh, hence, end crack tip information needs to be recomputed
                    endNeighbours.clear();
                    this->end.reassignContainer(m);
                    m.getNeighboursByPoint(this->end.container_polygon, endNeighbours);

                    endPoly_index = this->end.getRingPolygon(m, unusedEnd, endNeighbours);

                    Polygon& initRing = m.getPolygon(initPoly_index);
                    Polygon& endRing = m.getPolygon(endPoly_index);

                    Pair<int> toDeleteInit = crackPath.second();
                    Pair<int> toDeleteEnd = crackPath.secondToLast();

                    initRing.fixSegment(toDeleteInit, crackPath.first().first);
                    endRing.fixSegment(toDeleteEnd, crackPath.last().first);

                    std::vector<IndexSegment> toEraseInit = initRing.deleteVerticesInRange(toDeleteInit.first, toDeleteInit.second);
                    std::vector<IndexSegment> toEraseEnd = endRing.deleteVerticesInRange(toDeleteEnd.first, toDeleteEnd.second);
                    SegmentMap& edges = m.getSegments();

                    for (IndexSegment s: toEraseInit){
                        edges.delete_element(s);
                    }

                    for (IndexSegment s: toEraseEnd){
                        edges.delete_element(s);
                    }

                    radius = adjustBoxes(initRing, endRing, m.getPoints().getList());

                    initCrackEntry = initRing.getSurroundingVertices(crackPath.second());
                    endCrackEntry = endRing.getSurroundingVertices(crackPath.secondToLast());

                    initCrackEntry.orderCCW(m.getPoints().getList(), initRing.getCentroid());
                    endCrackEntry.orderCCW(m.getPoints().getList(), endRing.getCentroid());

                    initCrackPoints = {toDeleteInit, crackPath.first()};
                    endCrackPoints = {toDeleteEnd, crackPath.last()};
                }
            }

            this->init.remeshAndAdapt(radius, newP, initPoly_index, m, unusedInit, initAngle, initCrackEntry, initCrackPoints);
            m.printInFile("firstTip.txt");
            this->end.remeshAndAdapt(radius, newP, endPoly_index, m, unusedEnd, endAngle, endCrackEntry, endCrackPoints);
        }
    }else{
        this->prepareTip(this->init, oldP, newP, m, {crackPath.first(), crackPath.second()});
        this->prepareTip(this->end, oldP, newP, m,  {crackPath.last(), crackPath.secondToLast()});
    }

    return PolygonChangeData(oldP.getList(), newP);
}

void Crack::prepareTip(CrackTip &tip, UniqueList<Polygon> &oldP, std::vector<Polygon> &newP, BreakableMesh &mesh,
                       std::vector<Pair<int>> previousCrackPoints) {
    if(!tip.isFinished()){
        PolygonChangeData data = tip.prepareTip(mesh, StandardRadius, previousCrackPoints);

        oldP.push_list(data.oldPolygons);
        newP.insert(newP.end(), data.newPolygons.begin(), data.newPolygons.end());
    }
}

bool Crack::isFinished() {
    return init.isFinished() && end.isFinished();
}

void Crack::initializeCrack(BreakableMesh &mesh) {
    if(!mesh.isInDomain(this->init.getPoint()) || !mesh.isInDomain(this->end.getPoint())){
        throw std::invalid_argument("Invalid input. Crack lies outside the domain!");
    }

    this->init.reassignContainer(mesh);
    this->end.reassignContainer(mesh);

    UniqueList<Pair<int>> newPoints;
    mesh.breakMesh(this->init.container_polygon, PointSegment(this->init.getPoint(), this->end.getPoint()),
                   this->init.isFinished(), newPoints);
    this->crackPath.insert(newPoints.getList());
}

PolygonChangeData Crack::grow(Problem problem, Eigen::VectorXd u) {
    std::vector<Polygon> oldP;
    std::vector<Polygon> newP;

    UniqueList<Pair<int>> initCrackPoints, endCrackPoints;
    this->grow(this->init, oldP, newP, problem, u, initCrackPoints);
    this->crackPath.insert_front(initCrackPoints.getList());

    this->grow(this->end, oldP, newP, problem, u, endCrackPoints);
    this->crackPath.insert(endCrackPoints.getList());

    return PolygonChangeData(oldP, newP);
}


void Crack::grow(CrackTip &tip, std::vector<Polygon> &oldP, std::vector<Polygon> &newP, Problem problem, Eigen::VectorXd u,
                 UniqueList<Pair<int>> &crackPoints) {
    if(!tip.isFinished()){
        PolygonChangeData data = tip.grow(u, problem, crackPoints);

        oldP.insert(oldP.end(), data.oldPolygons.begin(), data.oldPolygons.end());
        newP.insert(newP.end(), data.newPolygons.begin(), data.newPolygons.end());
    }
}

double Crack::adjustBoxes(Polygon initPoly, Polygon endPoly, std::vector<Point> points) {
    double radius = this->StandardRadius;

    FractureConfig* config = FractureConfig::instance();
    while(!this->init.fitsBox(radius, initPoly, points) || !this->end.fitsBox(radius, endPoly, points)){
        radius = config->getRatio()*radius;
    }

    return radius;
}

void Crack::printInStream(std::ofstream &file) {
    int n = crackPath.size();

    file << n-1 << std::endl;

    for (int i = 0; i < n-1; ++i) {
        file << crackPath[i].first << " " << crackPath[(i+1)%n].first  << std::endl;
        file << crackPath[i].second << " " << crackPath[(i+1)%n].second  << std::endl;
    }
}


