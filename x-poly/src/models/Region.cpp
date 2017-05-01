#include <x-poly/models/Region.h>
#include <stdexcept>

Region::Region(std::vector<Point>& points) : Polygon(points){
    this->p = points;
}

void Region::mutate(std::vector<Point> &points) {
    this->p = points;
    Polygon::mutate(points);
}

Region::~Region() {}

Region::Region() : Polygon(){}

Region::Region(const Polygon &other, std::vector<Point>& points) : Polygon() {
    std::vector<int> otherPoints = other.getPoints();

    for (int i = 0; i < other.numberOfSides(); ++i) {
        this->p.push_back(points[otherPoints[i]]);
    }

    Polygon::mutate(this->p);
}


Region::Region(const Region &other) : Polygon(other){
    this->p = other.p;
    this->holes.assign(other.holes.begin(), other.holes.end());
}

std::vector<Hole>& Region::getHoles() {
    return this->holes;
}

std::vector<Point> Region::getSeedPoints() {
    return this->seedPoints;
}

void Region::addHole(Hole h) {
    //When we receive a hole we check whether the difference between the region and the hole is just
    //one path (according to the used library)
    XPolyConfig* config = XPolyConfig::instance();
    ClipperLib::Path region, hole;
    ClipperLib::Paths solution;

    for(int i=0;i<this->p.size(); i++){
        region << ClipperLib::IntPoint((int)(config->getScale()*this->p[i].getX()),
                                       (int)(config->getScale()*this->p[i].getY()));
    }

    std::vector<Point> holePoints = h.getPoints();
    for(int i=0;i<holePoints.size();i++){
        hole << ClipperLib::IntPoint((int)(config->getScale()*holePoints[i].getX()),
                                     (int)(config->getScale()*holePoints[i].getY()));
    }

    ClipperLib::Clipper clipper;
    clipper.AddPath(region, ClipperLib::ptSubject, true);
    clipper.AddPath(hole, ClipperLib::ptClip, true);
    clipper.Execute(ClipperLib::ctDifference, solution, ClipperLib::pftNonZero, ClipperLib::pftNonZero);

    if(solution.size()==1){
        //Hole does intersect, so Region has to change and the hole "dissapears"
        std::vector<Point> newPoints;

        for(int i=0;i<solution[0].size();i++){
            newPoints.push_back(Point(solution[0][i].X/(1.0*config->getScale()),
                                      solution[0][i].Y/(1.0*config->getScale())));
        }

        this->mutate(newPoints);
    }else{
        //Two cases, hole is completely inside or completely outside, just ignore holes outside

        if(Polygon::containsPoint(this->p, h.getCenter())){
            this->holes.push_back(h);
        }else{
            throw std::invalid_argument("Hole lies outside region");
        }
    }
}

void Region::generateSeedPoints(PointGenerator p, int nX, int nY){
    BoundingBox box = this->getBox();
    p.generate(this->seedPoints, box, nX, nY);
    this->clean();
}

void Region::addSeedPoints(std::vector<Point> seeds) {
    this->seedPoints.assign(seeds.begin(), seeds.end());
}

BoundingBox Region::getBox() {
    double xMin = LLONG_MAX;
    double xMax = LLONG_MIN;
    double yMin = LLONG_MAX;
    double yMax = LLONG_MIN;

    for(auto& v: p){
        xMin = v.getX()<xMin? v.getX(): xMin;
        xMax = v.getX()>xMax? v.getX(): xMax;
        yMin = v.getY()<yMin? v.getY(): yMin;
        yMax = v.getY()>yMax? v.getY(): yMax;
    }

    return BoundingBox(Point(xMin,yMin), Point(xMax,yMax));
}

void Region::clean() {
    std::vector<int> toKeep;
    std::vector<Point> newSeeds;

    for(int i = 0; i<seedPoints.size(); i++){
        if(Polygon::containsPoint(p,seedPoints[i])) toKeep.push_back(i);
    }

    for(int i=0; i<toKeep.size(); i++){
        newSeeds.push_back(seedPoints[toKeep[i]]);
    }

    this->seedPoints = newSeeds;
}


std::vector<Point> Region::getRegionPoints() {
    std::vector<Point> points;
    points.assign(this->p.begin(), this->p.end());

    for(int i=0;i<holes.size();i++){
        std::vector<Point> p = holes[i].getPoints();
        points.insert(points.end(), p.begin(), p.end());
    }

    return points;
}

void Region::getSegments(std::vector<IndexSegment> &s) {
    Polygon::getSegments(s);
    int offset = (int) this->p.size();

    for(Hole h : this->holes){
        h.getSegments(s, offset);
    }
}

bool Region::containsPoint(Point p) {
    std::vector<Point> regionPoints = this->p;

    return Polygon::containsPoint(regionPoints, p);
}

void Region::cleanSeedPoints() {
    this->seedPoints.clear();
}
