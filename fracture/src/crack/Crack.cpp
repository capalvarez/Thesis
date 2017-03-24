#include <fracture/crack/Crack.h>
#include <fracture/config/FractureConfig.h>
#include <fracture/geometry/mesh/SimplePolygonMerger.h>

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
    PointSegment crack (init, end);

    this->init = CrackTip(crack);
    this->end = CrackTip(PointSegment(end, init));
}

PolygonChangeData Crack::prepareTip(BreakableMesh &m) {
    UniqueList<Polygon> oldP;
    std::vector<Polygon> newP;
    UniqueList<Point> points = m.getPoints();

    if(this->init.container_polygon  == this->end.container_polygon ||
       m.polygonsTouch(this->init.container_polygon, this->end.container_polygon)){
        UniqueList<int> neighbours;
        this->init.getDirectNeighbours(this->init.container_polygon, m, neighbours);
        this->end.getDirectNeighbours(this->end.container_polygon, m, neighbours);

        neighbours.push_back(this->init.container_polygon);
        neighbours.push_back(this->end.container_polygon);

        int index = m.mergePolygons(neighbours.getList());
        Polygon ring = m.getPolygon(index);

        Point init_last = this->init.getPoint();
        double init_radius = this->init.StandardRadius;
        BoundingBox init_box(Point(init_last.getX()-init_radius, init_last.getY()-init_radius),
                         Point(init_last.getX()+init_radius, init_last.getY()+init_radius));

        Point end_last = this->end.getPoint();
        double end_radius = this->end.StandardRadius;
        BoundingBox end_box(Point(end_last.getX()-this->end.StandardRadius, end_last.getY()-this->end.StandardRadius),
                            Point(end_last.getX()+this->end.StandardRadius, end_last.getY()+this->end.StandardRadius));

        FractureConfig* config = FractureConfig::instance();


        while(!init_box.fitsInsidePolygon(ring, m)) {
            init_radius = config->getRatio()*init_radius;

            init_box = BoundingBox(Point(init_last.getX()-init_radius, init_last.getY()-init_radius),
                                   Point(init_last.getX()+init_radius, init_last.getY()+init_radius));
        }

        while(!end_box.fitsInsidePolygon(ring, m)) {
            end_radius = config->getRatio()*end_radius;

            end_box = BoundingBox(Point(end_last.getX()-end_radius, end_last.getY()-end_radius),
                                  Point(end_last.getX()+end_radius, end_last.getY()+end_radius));
        }

        while(init_box.intersects(end_box)){
            init_radius = config->getRatio()*init_radius;
            end_radius = config->getRatio()*end_radius;

            init_box = BoundingBox(Point(init_last.getX()-init_radius, init_last.getY()-init_radius),
                                   Point(init_last.getX()+init_radius, init_last.getY()+init_radius));
            end_box = BoundingBox(Point(end_last.getX()-end_radius, end_last.getY()-end_radius),
                                  Point(end_last.getX()+end_radius, end_last.getY()+end_radius));
        }

        Point p1 = end_box.getClosestTo(init_box.centroid());
        Point p2 = init_box.getClosestTo(end_box.centroid());

        Point middle = Point(std::abs(p1.getX()-p2.getX())/2, std::abs(p1.getY()-p2.getY())/2);
        double slope = PointSegment(init_box.centroid(), end_box.centroid()).perpendicularSlope();

        Point nextPoint(middle.getX()*2 , slope*middle.getX() + middle.getY());
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

        std::vector<int> affected1 = {index};
        std::vector<int> affected2 = {(m.getPolygons().size())-1};

        this->init.remeshAndAdapt(init_radius, newP, m.getPolygon(index), affected1, m);
        this->end.remeshAndAdapt(end_radius, newP, m.getPolygon(m.getPolygons().size()-1), affected2, m);

        for(int i: affected1){
            oldP.push_back(m.getPolygon(i));
        }

        for(int i: affected2){
            oldP.push_back(m.getPolygon(i));
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

PolygonChangeData Crack::initializeCrack(BreakableMesh& mesh) {
    int poly1 = mesh.findContainerPolygon(this->init.getPoint());
    init.assignLocation(poly1);

    PolygonChangeData change = mesh.breakMesh(poly1, PointSegment(this->init.getPoint(), this->end.getPoint()));
    end.assignLocation(change.lastPolygon);

    return change;
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
        PolygonChangeData data = tip.prepareTip(mesh);

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






