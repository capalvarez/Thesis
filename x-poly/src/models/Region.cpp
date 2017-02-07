#include <x-poly/models/Region.h>
#include <stdexcept>

Region::Region(std::vector<Point>& points) : Polygon(points){
    this->p = points;
    this->maxScale = 1000000;
}

void Region::mutate(std::vector<Point> &points) {
    this->p = points;
    Polygon::mutate(points);
}

Region::~Region() {}

Region::Region() : Polygon(){}

Region::Region(const Region &other) : Polygon(other){
    this->p = other.p;
    this->holes = other.holes;
    this->maxScale =  1000000;
}

std::vector<Hole*> Region::getHoles() {
    return this->holes;
}

std::vector<Point> Region::getSeedPoints() {
    return this->seedPoints;
}

void Region::addHole(Hole* h) {
    //When we receive a hole we check whether the difference between the region and the hole is just
    //one path (according to the used library)
    ClipperLib::Paths solution = ClipperWrapper::polyIntersection(this->p, h->getPoints(), maxScale);

    if(solution.size()==1){
        //Hole does intersect, so Region has to change and the hole "dissapears"
        std::vector<Point> newPoints;

        for(int i=0;i<solution[0].size();i++){
            newPoints.push_back(Point(solution[0][i].X/(1.0*maxScale), solution[0][i].Y/(1.0*maxScale)));
        }

        this->mutate(newPoints);
    }else{
        //Two cases, hole is completely inside or completely outside, just ignore holes outside

        if(Polygon::containsPoint(this->p, h->getCenter())){
            this->holes.push_back(h);
        }else{
            throw std::invalid_argument("Hole lies outside region");
        }
    }
}

void Region::generatePoints(PointGenerator p, int nX, int nY){
    BoundingBox box = this->getBox();
    p.generate(this->seedPoints, box, nX, nY);
    this->clean();
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
        std::vector<Point> p = holes[i]->getPoints();
        points.insert(points.end(), p.begin(), p.end());
    }

    return points;
}

void Region::getSegments(std::vector<Segment<int>> &s) {
    //TODO: Manage border cases here!
    // TODO: Don't quite remember the problem, needs studying

    Polygon::getSegments(s);
    int offset = (int) this->p.size();

    for(int i=0;i<holes.size();i++){
        holes[i]->getSegments(s, offset);
    }
}

bool Region::containsPoint(Point p) {
    return Polygon::containsPoint(this->p, p);
}




