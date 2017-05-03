#include <fracture/crack/Crack.h>
#include <fracture/config/FractureConfig.h>

Crack::Crack() {}

Crack::Crack(Point init, Point end, double speed, double ratio) {
    FractureConfig* config = FractureConfig::instance();
    config->setGrowthSpeed(speed);
    config->setCrackRatio(ratio);

    PointSegment crack (init, end);

    this->init = CrackTip(crack);
    this->end = CrackTip(PointSegment(end, init));
}

Crack::Crack(const Crack& c) {
    this->init = c.init;
    this->end = c.end;
}

Crack::Crack(Point init, Point end) {
    FractureConfig* config = FractureConfig::instance();
    PointSegment crack (init, end);

    this->init = CrackTip(crack);
    this->end = CrackTip(PointSegment(end, init));
    this->StandardRadius = config->getRatio()*crack.length();
}

PolygonChangeData Crack::prepareTip(BreakableMesh &m) {
    FractureConfig* config = FractureConfig::instance();

    UniqueList<Polygon> oldP;
    std::vector<Polygon> newP;
    UniqueList<Point> points = m.getPoints();

    bool bothAreGrowing = !this->init.hasFinished && !this->end.hasFinished;

    if(bothAreGrowing){
        if(this->init.container_polygon  == this->end.container_polygon ||
            m.polygonsTouch(this->init.container_polygon, this->end.container_polygon)){
            UniqueList<int> neighbours;
            this->init.getDirectNeighbours(this->init.container_polygon, m, neighbours);
            this->end.getDirectNeighbours(this->end.container_polygon, m, neighbours);

            neighbours.push_back(this->init.container_polygon);
            neighbours.push_back(this->end.container_polygon);

            std::vector<int> allPoints = m.getAllPoints(neighbours.getList());
            int index = m.mergePolygons(neighbours.getList());
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

            double dX = (p2.getX() - p1.getX());

            if(dX!=0){
                double slope = -dX/(p2.getY() - p1.getY());
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
            int neighbour1 = utilities::indexOf(neighbours.getList(), n_f.getFirst())!=-1? n_f.getSecond() : n_f.getFirst();

            Neighbours n_s = e.get(relevantSegments[1]);
            int neighbour2 = utilities::indexOf(neighbours.getList(), n_s.getFirst())!=-1? n_s.getSecond() : n_s.getFirst();

            NeighbourInfo n1 = NeighbourInfo(index, relevantSegments[0], intersections[0], false);
            NeighbourInfo n2 = NeighbourInfo(neighbour2, relevantSegments[1], intersections[1], false);

            m.splitPolygons(n1, n2, neighbour1, oldP.getList(), newP);

            int poly1 = m.getPolygon(index).containsPoint(m.getPoints().getList(), this->init.getPoint())?
                        index : (int)(m.getPolygons().size())-1;
            int poly2 = poly1==index? (int)(m.getPolygons().size())-1 : index;

            m.printInFile("beforePreparing.txt");

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

            this->init.remeshAndAdapt(radius, newP, poly1, m, toPoly1);
            this->end.remeshAndAdapt(radius, newP, poly2, m, toPoly2);

            oldP.push_back(m.getPolygon(poly1));
            oldP.push_back(m.getPolygon(poly2));
        }else{
            double radius;
            int initPoly_index, endPoly_index;
            std::vector<int> unusedInit, unusedEnd, affectedPolygons;

            if(this->init.fitsBox(StandardRadius, m.getPolygon(this->init.container_polygon), m.getPoints().getList())
               && this->end.fitsBox(StandardRadius, m.getPolygon(this->end.container_polygon), m.getPoints().getList())){
                radius = StandardRadius;
                initPoly_index = this->init.container_polygon;
                endPoly_index = this->end.container_polygon;

                affectedPolygons.push_back(initPoly_index);
                affectedPolygons.push_back(endPoly_index);
            } else {
                if(this->init.fitsBox(StandardRadius*config->getRatio(), m.getPolygon(this->init.container_polygon), m.getPoints().getList())
                   && this->end.fitsBox(StandardRadius*config->getRatio(), m.getPolygon(this->end.container_polygon), m.getPoints().getList())){
                    radius = StandardRadius*config->getRatio();
                    initPoly_index = this->init.container_polygon;
                    endPoly_index = this->end.container_polygon;

                    affectedPolygons.push_back(initPoly_index);
                    affectedPolygons.push_back(endPoly_index);
                }else{
                    initPoly_index = this->init.getRingPolygon(m, unusedInit, affectedPolygons);
                    endPoly_index = this->end.getRingPolygon(m, unusedEnd, affectedPolygons);

                    Polygon initRing = m.getPolygon(initPoly_index);
                    Polygon endRing = m.getPolygon(endPoly_index);

                    radius = adjustBoxes(initRing, endRing, m.getPoints().getList());
                }
            }

            this->init.remeshAndAdapt(radius, newP, initPoly_index, m, unusedInit);
            this->end.remeshAndAdapt(radius, newP, endPoly_index, m, unusedEnd);

            for (int i: affectedPolygons){
                oldP.push_back(m.getPolygon(i));
            }
        }
    }else{
        this->prepareTip(this->init, oldP, newP, m);
        this->prepareTip(this->end, oldP, newP, m);
    }

    return PolygonChangeData(oldP.getList(), newP);
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
    mesh.breakMesh(this->init.container_polygon, PointSegment(this->init.getPoint(), this->end.getPoint()), this->init.isFinished());
}

PolygonChangeData Crack::grow(Problem problem, Eigen::VectorXd u) {
    std::vector<Polygon> oldP;
    std::vector<Polygon> newP;

    problem.mesh->printInFile("changed.txt");

    this->grow(this->init, oldP, newP, problem, u);
    this->grow(this->end, oldP, newP, problem, u);

    return PolygonChangeData(oldP, newP);
}

void Crack::prepareTip(CrackTip tip, UniqueList<Polygon> &oldP, std::vector<Polygon> &newP, BreakableMesh &mesh) {
    if(!tip.isFinished()){
        PolygonChangeData data = tip.prepareTip(mesh, StandardRadius);

        oldP.push_list(data.oldPolygons);
        newP.insert(newP.end(), data.newPolygons.begin(), data.newPolygons.end());
    }
}

void Crack::grow(CrackTip &tip, std::vector<Polygon> &oldP, std::vector<Polygon> &newP, Problem problem,
                 Eigen::VectorXd u) {
    if(!tip.isFinished()){
        PolygonChangeData data = tip.grow(u, problem);

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




